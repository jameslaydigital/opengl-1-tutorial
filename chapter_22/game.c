/*
 * Chapter 22: Final Project - "Cosmic Defender"
 * A complete 3D space shooter demonstrating all OpenGL 1.1 techniques
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

/* Configuration */
#define MAX_ENEMIES 20
#define MAX_PROJECTILES 50
#define MAX_PARTICLES 100
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

/* Game states */
typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER
} game_state_t;

/* Entity structures */
typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float rotation;
    int active;
} entity_t;

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float life;
    float r, g, b;
    int active;
} particle_t;

/* Game state */
static struct {
    game_state_t state;
    
    /* Player */
    float player_x, player_y, player_z;
    float player_rotation;
    int player_health;
    int player_score;
    
    /* Entities */
    entity_t enemies[MAX_ENEMIES];
    entity_t projectiles[MAX_PROJECTILES];
    particle_t particles[MAX_PARTICLES];
    
    /* Game logic */
    int wave;
    int enemies_killed;
    float spawn_timer;
    int last_time;
    
    /* Input */
    int keys[256];
    int mouse_x;
    int mouse_initialized;
} game = {
    .state = STATE_MENU,
    .player_x = 0, .player_y = 0, .player_z = 0,
    .player_rotation = 0,
    .player_health = 100,
    .player_score = 0,
    .wave = 1,
    .enemies_killed = 0,
    .spawn_timer = 0,
    .mouse_initialized = 0
};

/* Utility functions */
float randf(void) {
    return (float)rand() / RAND_MAX;
}

float dist3d(float x1, float y1, float z1, float x2, float y2, float z2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;
    return sqrtf(dx*dx + dy*dy + dz*dz);
}

/* Particle system */
void spawn_explosion(float x, float y, float z, float r, float g, float b) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!game.particles[i].active) {
            game.particles[i].x = x;
            game.particles[i].y = y;
            game.particles[i].z = z;
            game.particles[i].vx = (randf() - 0.5f) * 0.05f;  /* Reduced particle speed to 25% */
            game.particles[i].vy = (randf() - 0.5f) * 0.05f;
            game.particles[i].vz = (randf() - 0.5f) * 0.05f;
            game.particles[i].life = 1.0f;
            game.particles[i].r = r;
            game.particles[i].g = g;
            game.particles[i].b = b;
            game.particles[i].active = 1;
            
            if ((i % 3) == 0) break; /* Spawn 1/3 of particles */
        }
    }
}

void update_particles(float dt) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game.particles[i].active) {
            game.particles[i].x += game.particles[i].vx * dt;
            game.particles[i].y += game.particles[i].vy * dt;
            game.particles[i].z += game.particles[i].vz * dt;
            game.particles[i].life -= dt * 0.01f;
            
            if (game.particles[i].life <= 0) {
                game.particles[i].active = 0;
            }
        }
    }
}

void draw_particles(void) {
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDepthMask(GL_FALSE);
    
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game.particles[i].active) {
            float alpha = game.particles[i].life;
            glColor4f(game.particles[i].r, game.particles[i].g, 
                     game.particles[i].b, alpha);
            glVertex3f(game.particles[i].x, game.particles[i].y, 
                      game.particles[i].z);
        }
    }
    glEnd();
    
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

/* Player functions */
void draw_player_ship(void) {
    glPushMatrix();
    glTranslatef(game.player_x, game.player_y, game.player_z);
    glRotatef(game.player_rotation, 0, 1, 0);
    
    /* Ship body - cyan */
    GLfloat mat_diffuse[] = {0.0f, 0.8f, 1.0f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0f);
    
    glPushMatrix();
    glScalef(0.3f, 0.15f, 0.6f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    /* Wings */
    glPushMatrix();
    glTranslatef(0.4f, 0, -0.1f);
    glScalef(0.4f, 0.05f, 0.3f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.4f, 0, -0.1f);
    glScalef(0.4f, 0.05f, 0.3f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}

void shoot_projectile(void) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (!game.projectiles[i].active) {
            game.projectiles[i].x = game.player_x;
            game.projectiles[i].y = game.player_y;
            game.projectiles[i].z = game.player_z;
            
            float rad = game.player_rotation * 0.017453f;
            game.projectiles[i].vx = sinf(rad) * 0.125f;  /* Reduced speed to 25% */
            game.projectiles[i].vz = cosf(rad) * 0.125f;  /* Reduced speed to 25% */
            game.projectiles[i].vy = 0;
            
            game.projectiles[i].active = 1;
            break;
        }
    }
}

/* Enemy functions */
void spawn_enemy(void) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!game.enemies[i].active) {
            float angle = randf() * 6.28f;
            float dist = 30.0f + randf() * 20.0f;
            
            game.enemies[i].x = game.player_x + sinf(angle) * dist;
            game.enemies[i].y = randf() * 4.0f - 2.0f;
            game.enemies[i].z = game.player_z + cosf(angle) * dist;
            game.enemies[i].rotation = 0;
            game.enemies[i].active = 1;
            break;
        }
    }
}

void draw_enemy(entity_t* enemy) {
    glPushMatrix();
    glTranslatef(enemy->x, enemy->y, enemy->z);
    glRotatef(enemy->rotation, 0, 1, 0);
    
    /* Enemy ship - red */
    GLfloat mat_diffuse[] = {1.0f, 0.2f, 0.0f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 0.5f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);
    
    glutSolidSphere(0.3, 10, 10);
    
    /* Spikes */
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glutSolidCone(0.15, 0.5, 8, 1);
    glPopMatrix();
    
    glPopMatrix();
}

void update_enemies(float dt) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (game.enemies[i].active) {
            /* Move toward player */
            float dx = game.player_x - game.enemies[i].x;
            float dy = game.player_y - game.enemies[i].y;
            float dz = game.player_z - game.enemies[i].z;
            float dist = sqrtf(dx*dx + dy*dy + dz*dz);
            
            if (dist > 0.1f) {
                float speed = 0.0125f * (1.0f + game.wave * 0.1f);  /* Reduced to 25% */
                game.enemies[i].x += (dx / dist) * speed * dt;
                game.enemies[i].y += (dy / dist) * speed * dt;
                game.enemies[i].z += (dz / dist) * speed * dt;
            }
            
            game.enemies[i].rotation += dt * 0.025f;  /* Reduced rotation speed */
            
            /* Check collision with player */
            if (dist < 1.0f) {
                game.player_health -= 10;
                spawn_explosion(game.enemies[i].x, game.enemies[i].y, 
                              game.enemies[i].z, 1.0f, 0.3f, 0.0f);
                game.enemies[i].active = 0;
                
                if (game.player_health <= 0) {
                    game.state = STATE_GAME_OVER;
                }
            }
        }
    }
}

/* Projectile functions */
void draw_projectile(entity_t* proj) {
    glPushMatrix();
    glTranslatef(proj->x, proj->y, proj->z);
    
    GLfloat mat_emission[] = {0.5f, 1.0f, 0.5f, 1.0f};
    GLfloat mat_diffuse[] = {0.2f, 1.0f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glutSolidSphere(0.1, 8, 8);
    
    GLfloat no_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    
    glPopMatrix();
}

void update_projectiles(float dt) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (game.projectiles[i].active) {
            game.projectiles[i].x += game.projectiles[i].vx * dt;
            game.projectiles[i].y += game.projectiles[i].vy * dt;
            game.projectiles[i].z += game.projectiles[i].vz * dt;
            
            /* Check distance from player (despawn far projectiles) */
            float dist = dist3d(game.projectiles[i].x, game.projectiles[i].y, 
                               game.projectiles[i].z, game.player_x, 
                               game.player_y, game.player_z);
            if (dist > 50.0f) {
                game.projectiles[i].active = 0;
                continue;
            }
            
            /* Check collision with enemies */
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (game.enemies[j].active) {
                    float enemy_dist = dist3d(game.projectiles[i].x, 
                                             game.projectiles[i].y, 
                                             game.projectiles[i].z,
                                             game.enemies[j].x, 
                                             game.enemies[j].y, 
                                             game.enemies[j].z);
                    if (enemy_dist < 0.5f) {
                        game.projectiles[i].active = 0;
                        game.enemies[j].active = 0;
                        game.player_score += 100;
                        game.enemies_killed++;
                        spawn_explosion(game.enemies[j].x, game.enemies[j].y, 
                                      game.enemies[j].z, 1.0f, 0.5f, 0.0f);
                        break;
                    }
                }
            }
        }
    }
}

/* Environment */
void draw_grid(void) {
    glDisable(GL_LIGHTING);
    glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_LINES);
    for (int i = -50; i <= 50; i += 2) {
        glVertex3f(i, -3, -50);
        glVertex3f(i, -3, 50);
        glVertex3f(-50, -3, i);
        glVertex3f(50, -3, i);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void draw_starfield(void) {
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    srand(12345); /* Fixed seed for consistent stars */
    for (int i = 0; i < 200; i++) {
        float brightness = 0.5f + randf() * 0.5f;
        glColor3f(brightness, brightness, brightness);
        float x = (randf() - 0.5f) * 100.0f;
        float y = randf() * 30.0f + 10.0f;
        float z = (randf() - 0.5f) * 100.0f;
        glVertex3f(x, y, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

/* HUD */
void draw_text(int x, int y, const char* text) {
    glRasterPos2i(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void draw_hud(void) {
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    
    char buffer[256];
    
    if (game.state == STATE_MENU) {
        glColor3f(1, 1, 1);
        draw_text(w/2 - 150, h/2 + 50, "COSMIC DEFENDER");
        draw_text(w/2 - 100, h/2, "Press SPACE to Start");
        draw_text(w/2 - 120, h/2 - 50, "WASD: Move  Space: Shoot");
        draw_text(w/2 - 80, h/2 - 80, "Mouse: Turn");
    } else if (game.state == STATE_PLAYING || game.state == STATE_PAUSED) {
        /* Health bar */
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2i(20, h - 40);
        glVertex2i(220, h - 40);
        glVertex2i(220, h - 20);
        glVertex2i(20, h - 20);
        glEnd();
        
        float health_ratio = game.player_health / 100.0f;
        glColor3f(1.0f - health_ratio, health_ratio, 0);
        glBegin(GL_QUADS);
        glVertex2i(20, h - 40);
        glVertex2i(20 + (int)(200 * health_ratio), h - 40);
        glVertex2i(20 + (int)(200 * health_ratio), h - 20);
        glVertex2i(20, h - 20);
        glEnd();
        
        /* Stats */
        glColor3f(1, 1, 1);
        sprintf(buffer, "Health: %d", game.player_health);
        draw_text(230, h - 35, buffer);
        
        sprintf(buffer, "Score: %d", game.player_score);
        draw_text(20, h - 60, buffer);
        
        sprintf(buffer, "Wave: %d", game.wave);
        draw_text(20, h - 80, buffer);
        
        if (game.state == STATE_PAUSED) {
            glColor3f(1, 1, 0);
            draw_text(w/2 - 50, h/2, "PAUSED");
            draw_text(w/2 - 80, h/2 - 30, "Press P to Continue");
        }
    } else if (game.state == STATE_GAME_OVER) {
        glColor3f(1, 0, 0);
        draw_text(w/2 - 80, h/2 + 50, "GAME OVER");
        glColor3f(1, 1, 1);
        sprintf(buffer, "Final Score: %d", game.player_score);
        draw_text(w/2 - 80, h/2, buffer);
        sprintf(buffer, "Wave Reached: %d", game.wave);
        draw_text(w/2 - 90, h/2 - 30, buffer);
        draw_text(w/2 - 100, h/2 - 70, "Press R to Restart");
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

/* Game logic */
void reset_game(void) {
    game.state = STATE_PLAYING;
    game.player_x = 0;
    game.player_y = 0;
    game.player_z = 0;
    game.player_rotation = 0;
    game.player_health = 100;
    game.player_score = 0;
    game.wave = 1;
    game.enemies_killed = 0;
    game.spawn_timer = 0;
    
    for (int i = 0; i < MAX_ENEMIES; i++) game.enemies[i].active = 0;
    for (int i = 0; i < MAX_PROJECTILES; i++) game.projectiles[i].active = 0;
    for (int i = 0; i < MAX_PARTICLES; i++) game.particles[i].active = 0;
}

void update_game(float dt) {
    if (game.state != STATE_PLAYING) return;
    
    /* Player movement - reduced to 25% speed */
    float speed = 0.025f * dt;
    float rad = game.player_rotation * 0.017453f;
    
    if (game.keys['w'] || game.keys['W']) {
        game.player_x += sinf(rad) * speed;
        game.player_z += cosf(rad) * speed;
    }
    if (game.keys['s'] || game.keys['S']) {
        game.player_x -= sinf(rad) * speed;
        game.player_z -= cosf(rad) * speed;
    }
    if (game.keys['a'] || game.keys['A']) {
        game.player_x += cosf(rad) * speed;  /* Fixed: was - */
        game.player_z -= sinf(rad) * speed;  /* Fixed: was + */
    }
    if (game.keys['d'] || game.keys['D']) {
        game.player_x -= cosf(rad) * speed;  /* Fixed: was + */
        game.player_z += sinf(rad) * speed;  /* Fixed: was - */
    }
    
    /* Update entities */
    update_enemies(dt);
    update_projectiles(dt);
    update_particles(dt);
    
    /* Enemy spawning */
    game.spawn_timer += dt;
    int enemies_per_wave = 3 + game.wave;
    if (game.spawn_timer > 2000.0f / (1.0f + game.wave * 0.2f)) {
        int active_count = 0;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (game.enemies[i].active) active_count++;
        }
        
        if (active_count < enemies_per_wave) {
            spawn_enemy();
            game.spawn_timer = 0;
        }
    }
    
    /* Wave progression */
    if (game.enemies_killed >= enemies_per_wave * 3) {
        game.wave++;
        game.enemies_killed = 0;
        game.player_health = (game.player_health < 80) ? game.player_health + 20 : 100;
    }
}

/* OpenGL setup */
void init_gl(void) {
    glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    
    /* Main light */
    GLfloat light0_ambient[] = {0.3f, 0.3f, 0.4f, 1};
    GLfloat light0_diffuse[] = {0.8f, 0.8f, 1.0f, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    
    /* Secondary light */
    GLfloat light1_diffuse[] = {0.4f, 0.2f, 0.2f, 1};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /* Camera follows player */
    float cam_dist = 8.0f;
    float cam_height = 4.0f;
    float rad = game.player_rotation * 0.017453f;
    float cam_x = game.player_x - sinf(rad) * cam_dist;
    float cam_z = game.player_z - cosf(rad) * cam_dist;
    
    gluLookAt(cam_x, game.player_y + cam_height, cam_z,
              game.player_x, game.player_y, game.player_z,
              0, 1, 0);
    
    /* Lighting */
    GLfloat light0_pos[] = {game.player_x + 10, 20, game.player_z + 10, 1};
    GLfloat light1_pos[] = {game.player_x - 10, 5, game.player_z - 10, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    
    /* Draw scene */
    if (game.state != STATE_MENU) {
        draw_grid();
        draw_starfield();
        draw_player_ship();
        
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (game.enemies[i].active) draw_enemy(&game.enemies[i]);
        }
        
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (game.projectiles[i].active) draw_projectile(&game.projectiles[i]);
        }
        
        draw_particles();
    }
    
    /* HUD */
    draw_hud();
    
    glutSwapBuffers();
}

void idle(void) {
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    float dt = (current_time - game.last_time);
    game.last_time = current_time;
    
    update_game(dt);
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w/h, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    game.keys[key] = 1;
    
    if (key == 27) exit(0); /* ESC */
    
    if (key == ' ') {
        if (game.state == STATE_MENU) {
            reset_game();
        } else if (game.state == STATE_PLAYING) {
            shoot_projectile();
        }
    }
    
    if ((key == 'p' || key == 'P') && game.state == STATE_PLAYING) {
        game.state = STATE_PAUSED;
    } else if ((key == 'p' || key == 'P') && game.state == STATE_PAUSED) {
        game.state = STATE_PLAYING;
    }
    
    if ((key == 'r' || key == 'R') && game.state == STATE_GAME_OVER) {
        reset_game();
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    (void)x; (void)y;
    game.keys[key] = 0;
}

void special(int key, int x, int y) {
    (void)x; (void)y;
    /* Arrow keys no longer used for rotation - mouse motion is used instead */
    (void)key;
}

void mouse_motion(int x, int y) {
    (void)y; /* Only use horizontal motion */
    
    if (!game.mouse_initialized) {
        game.mouse_x = x;
        game.mouse_initialized = 1;
        return;
    }
    
    if (game.state == STATE_PLAYING) {
        int delta_x = x - game.mouse_x;
        game.player_rotation -= delta_x * 0.2f; /* Mouse sensitivity */
    }
    
    game.mouse_x = x;
}

int main(int argc, char** argv) {
    printf("===========================================\n");
    printf("  COSMIC DEFENDER - Final Project\n");
    printf("===========================================\n");
    printf("A complete 3D space shooter demonstrating\n");
    printf("all OpenGL 1.1 techniques from the tutorial!\n\n");
    printf("Controls:\n");
    printf("  WASD       - Move\n");
    printf("  Mouse      - Turn\n");
    printf("  Space      - Shoot\n");
    printf("  P          - Pause\n");
    printf("  R          - Restart\n");
    printf("  ESC        - Quit\n\n");
    printf("Survive the waves and rack up points!\n");
    printf("===========================================\n\n");
    
    srand(time(NULL));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Cosmic Defender - OpenGL 1.1 Final Project");
    
    init_gl();
    game.last_time = glutGet(GLUT_ELAPSED_TIME);
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(special);
    glutPassiveMotionFunc(mouse_motion);
    glutMotionFunc(mouse_motion);
    
    /* Hide cursor for immersive gameplay */
    glutSetCursor(GLUT_CURSOR_NONE);
    
    glutMainLoop();
    return 0;
}

