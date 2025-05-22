#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

float light = 1.0;

void init_scene(Scene* scene)
{
    scene->enableCar=false;
    scene->get_in=false;
    scene->isAli=false;
    scene->isMenuActive=true;
    scene->aliLength=6;
    scene->fog=false;
    //map
    scene->cube_rows = 5;
    scene->cube_columns = 40;
    scene->cube_length = scene->cube_rows * scene->cube_columns;
    scene->cube = (Entity*) malloc(sizeof(Entity)*(scene->cube_length));
    for (size_t row = 0; row < scene->cube_rows; row++)
    {
        for (size_t col = 0; col < scene->cube_columns; col++)
        {
            size_t index = row * scene->cube_columns + col;
            init_Entity(&(scene->cube[index]), "assets/models/cube.obj", "assets/textures/road.png");
            scene->cube[index].pos.x = col * 1.0f - 3.0f; // A kockák egymástól való távolsága
            scene->cube[index].pos.y = row * 1.0f - 3.0f; // A platform magassága
            scene->cube[index].pos.z = 0.0f; // A kockák egymástól való távolsága
            //printf("pozicio: %zu, %f, %f, %f\n", index, scene->cube[index].pos.x, scene->cube[index].pos.y, scene->cube[index].pos.z);
        }

    }
    int gap=4;
    scene->ali=(Entity*) malloc(sizeof(Entity)*(scene->aliLength));

    for (size_t i = 0; i < 6; i++)
    {
        init_Entity(&(scene->ali[i]), "assets/models/cube.obj", "assets/textures/grandma.jpg");
        
            scene->ali[i].pos.y=1.5;

        if (i>0)
        {   gap+=5;
            scene->ali[i].pos.x=gap;
            
        }else{
           scene->ali[i].pos.x=gap; 
        }
        printf("Ali[%d].x=%d",i,gap);
        
        scene->ali[i].pos.z=1;
        //scene->ali[i].scale.y=1.5;
        scene->ali[i].rot.x+=90;
    }
    

    init_Entity(&(scene->car), "assets/models/porsche.obj", "assets/textures/cube.png");
    //init_Entity(&(scene->ali), "assets/models/cube.obj", "assets/textures/ali.jpg");
    
    scene->car.pos.z=0.78;
    scene->car.pos.x=0;
    scene->car.pos.y=-1;
    scene->car.rot.y+=90.0;
    scene->car.rot.x+=90.0;
    scene->car.rot.y+=180.0;
    
    scene->car.scale.x=0.5;
    scene->car.scale.y=0.5;
    scene->car.scale.z=0.5;
    /*
    scene->ali.pos.y=1;
    scene->ali.pos.x=6;
    scene->ali.pos.z=1;
    scene->ali.scale.y=2;
    scene->ali.rot.x+=90;
    */

    //glBindTexture(GL_TEXTURE_2D, scene->cube.texture_id);

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    // Load get in the car texture
    scene->get_inTexture = load_texture("assets/textures/get_in.jpg");
    if (scene->get_inTexture == 0) {
        printf("[ERROR] Failed to load texture get_in.jpg\n");
    }
    // Load hit ali texture
    scene->getAliTexture = load_texture("assets/textures/collision.jpg");
    if (scene->get_inTexture == 0) {
        printf("[ERROR] Failed to load texture collision.jpg\n");
    }
    // Load menu texture
    scene->menuTexture = load_texture("assets/textures/menu.jpg");
    if (scene->menuTexture == 0) {
        printf("[ERROR] Failed to load texture menu.jpg\n");
    }
    // Load game over texture
    scene->overTexture = load_texture("assets/textures/over.jpg");
    if (scene->menuTexture == 0) {
        printf("[ERROR] Failed to load texture over.jpg\n");
    }
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void moveAli_sin(Entity* ali){
    static double radian = 0.0; 
    ali->pos.y = -1.0 + 2.0 * sin(radian); 
    radian += 0.002; 
}

void moveAli_cos(Entity* ali){
    static double radian = 0.0; 
    ali->pos.y = -1.0 + 2.0 * cos(radian); 
    radian += 0.002; 
}

void update_scene(Scene* scene)
{
    for (size_t i = 0; i < scene->aliLength; i++)
    {   
        if (i%2==0)
        {
           moveAli_cos(&(scene->ali[i]));
        }else{
            moveAli_sin(&(scene->ali[i]));
            }
        
        
    }
    
   
    if (scene->get_in)
    {
        sleep(1);
        scene->get_in=false;
    }
    if (scene->isAli)
    {
        sleep(1);
        scene->isAli=false;
    }
    
    
}

void set_light_plus(){
    light+=0.2;
}

void set_light_minus(){
    light-=0.2;
}

void set_lighting()
{
    float ambient_light[] = { 0.5f * light, 0.5f * light, 0.5f * light, 1.0f };
    float diffuse_light[] = { 1.0f * light, 1.0f * light, 1.0 * light, 1.0f };
    float specular_light[] = { 0.0f * light, 0.0f * light, 0.0f * light, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

}

void render_scene(Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    for (size_t i = 0; i < scene->cube_length; i++)
    {
        render_obj(&(scene->cube[i]));

    }
    for (size_t i = 0; i < scene->aliLength; i++)
    {
        render_obj(&(scene->ali[i]));
    }
    
    render_obj(&(scene->car));
    //render_obj(&(scene->ali));
    if (scene->isMenuActive)
    {
         render_menu_texture(scene->menuTexture);
        
        // Repair the texture settings
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0); 
    }
    

    if (scene->get_in)
    {
        // Draw the menu texture
        render_menu_texture(scene->get_inTexture);
        
        // Repair the texture settings
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0); 
        
    }
    if (scene->car.pos.x>=scene->ali[5].pos.x+1.5)
    {
        // Draw the menu texture
        render_menu_texture(scene->overTexture);
        
        // Repair the texture settings
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0); 
        
    }

    if (scene->isAli)
    {
        // Draw the menu texture
        render_menu_texture(scene->getAliTexture);
        
        // Repair the texture settings
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0); 
    }else{
        // Menükép nem aktív, ezért újra összekapcsoljuk az objektumokhoz a textúrákat
        glEnable(GL_TEXTURE_2D);
        for (size_t i = 0; i < scene->cube_length; i++)
        {
            glBindTexture(GL_TEXTURE_2D, scene->cube[i].texture_id);
        }
        glBindTexture(GL_TEXTURE_2D, scene->car.texture_id);
        for (size_t i = 0; i < scene->aliLength; i++)
        {
            glBindTexture(GL_TEXTURE_2D, scene->ali[i].texture_id);
        }
        
        
    }
    
    if (scene->fog)
    {
        glEnable(GL_FOG);
    }
    else
    {
        glDisable(GL_FOG);
    }
    

}

void render_obj(const Entity* entity){
    //helyes sorrend!
    glPushMatrix();//rajzolás előtt
    glBindTexture(GL_TEXTURE_2D, entity->texture_id);
    glTranslatef(entity->pos.x, entity->pos.y, entity->pos.z);
    glRotatef(entity->rot.x, 1, 0, 0);
    glRotatef(entity->rot.y, 0, 1, 0);
    glRotatef(entity->rot.z, 0, 0, 1);
    glScalef(entity->scale.x, entity->scale.y, entity->scale.z);
    draw_model(&(entity->model));
    glPopMatrix();
}

void render_menu_texture(GLuint texture) {
    if (texture != 0) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, 800, 600, 0, -1, 1);  

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex2f(800.0, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex2f(800.0, 600.0);
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 600.0);
        glEnd();
        
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
}
void draw_origin()

{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void destroy_scene(Scene* scene){
    free(&(scene->cube));
    free(&(scene->ali));
}