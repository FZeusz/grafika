#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Cube!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Köd inicializálása
    glEnable(GL_FOG);
    glFogf(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, 0.5f);
    glFogf(GL_FOG_START, 1.0f); // A köd kezdete (GL_LINEAR esetén)
    glFogf(GL_FOG_END, 5.0f); // A köd vége (GL_LINEAR esetén)
    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f}; // A köd színe
    glFogfv(GL_FOG_COLOR, fogColor);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                if (app->scene.enableCar)
                {
                    set_camera_speed(&(app->camera), 1.5);
                }else{
                    set_camera_speed(&(app->camera), 1);
                }
                
                
                break;
            case SDL_SCANCODE_S:
                if (app->scene.car.pos.x>=app->scene.ali[5].pos.x)
                {
                    
                }else set_camera_speed(&(app->camera), -1);
                
               
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_E:
                app->scene.enableCar=!app->scene.enableCar;
                app->scene.get_in=true;
                app->scene.one=1;
                app->camera.position.x=app->camera.position.x-2;
                app->camera.position.y=app->scene.car.pos.y;
                break;
            case SDL_SCANCODE_F1:
                app->scene.isMenuActive=!app->scene.isMenuActive;
                break;
            case SDL_SCANCODE_KP_PLUS:
                set_light_plus();
                break;
            case SDL_SCANCODE_KP_MINUS:
                set_light_minus();
                break;
            case SDL_SCANCODE_F2:
                app->scene.fog=!app->scene.fog;
                break;
            case SDL_SCANCODE_F3:
                if (app->scene.enableCar)
                {
                    app->camera.position.x = 0;
                    app->camera.position.y = -1;
                }
                
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));
    

   // printf("Camera x pos: %f\n", app->camera.position.x);
    //printf("Camera y pos: %f\n", app->camera.position.y);

    if (app->scene.enableCar)
    {   
        
        if (app->scene.one==1)
        {
           app->scene.get_in=true;
            app->scene.one=2;
        }

        app->camera.position.z=2;
        app->scene.car.pos.x=app->camera.position.x+2;
        app->scene.car.pos.y=app->camera.position.y;
        // Check car positon
        if (app->camera.position.y > 1) {
         app->camera.position.y = 1;
        } else if (app->camera.position.y < -3) {
        app->camera.position.y = -3;
        }
        //Collison detection
        for (size_t i = 0; i < app->scene.aliLength; i++)
        {
        if (fabs(app->scene.car.pos.x - app->scene.ali[i].pos.x)<=1.5 && fabs(app->scene.car.pos.y - app->scene.ali[i].pos.y)<=1)
        {
        app->scene.isAli=true;
        app->camera.position.x=-2.0;
        app->camera.position.y=-1.0;
        break;
        }
        }
    
    }else{
        app->camera.position.z=1;
    }
    
    
    
    
   
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
   
    
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{   
    destroy_scene(&(app->scene));
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
