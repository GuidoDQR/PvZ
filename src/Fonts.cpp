#include "Fonts.hpp"

Tyra::Sprite spr_font_BrianneTod12;
Tyra::Sprite spr_textFont[160];

bool Load_sprite_text_font(Tyra::Engine* engine){
    LoadSprite(&spr_font_BrianneTod12,Tyra::Vec2(0,0),Tyra::Vec2(10,17));
    LoadTexture(&spr_font_BrianneTod12,"FONTS/BRIANNETOD/12/_BrianneTod12alpha.png",engine);
    spr_font_BrianneTod12.mode = Tyra::SpriteMode::MODE_REPEAT;
    
    std::string file;

    // Load max 92
    for(int i=0;i<92;i++){
        LoadSprite(&spr_textFont[i],Tyra::Vec2(0,0),Tyra::Vec2(BriannedTod12Width[i],17),Tyra::SpriteMode::MODE_REPEAT);
        file  = "FONTS/BRIANNETOD/12/";
        file +=  std::to_string(i); 
        file += ".PNG";
        LoadTexture(&spr_textFont[i],file.c_str(),engine);
    }

    /*for(int i =0 ;i< charSize;i++ ){

        printf("pos: %d. char: %d\n",i,BriannedTodChar[i]);
    }*/
    return true;
} 

void DrawText(std::string text, int x, int y){

    unsigned int maxLetter = text.size();   
    int spaceLetter = 1;
    int offsetX = 0;
    int offsetY = 0;

    int ascii;
    int sprPos;
    for(unsigned int i=0; i<maxLetter;i++){
        ascii = text[i];
        sprPos = ' ';

        for(int i=0;i<charSize;i++){
            if(ascii == BriannedTodChar[i]){
                sprPos = i;
            }
        }

        //printf("pos: %d. ascii: %d. sprPos: %d\n",i,ascii,sprPos);
        
        if(ascii == '\n'){
                offsetY += 18;
                offsetX = 0;
        }else{
            spr_textFont[sprPos].position.x = x + offsetX;
            spr_textFont[sprPos].position.y = y + offsetY;

            if(sprPos != ' '){
                engine->renderer.renderer2D.render(spr_textFont[sprPos]);
                offsetX += spr_textFont[sprPos].size.x + spaceLetter;
            }else{ offsetX += 12 + spaceLetter; }
        }

    }
    
}

void ChangeColorFont(Tyra::Color newColor){
    for(int i=0;i < 100;i++){
        spr_textFont[i].color.r = newColor.r;
        spr_textFont[i].color.g = newColor.g;
        spr_textFont[i].color.b = newColor.b;
        spr_textFont[i].color.a = newColor.a;
    }
}