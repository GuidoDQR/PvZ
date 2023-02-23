#include "Fonts.hpp"

Tyra::Sprite spr_font_BrianneTod12;
Tyra::Sprite spr_textFont[100];

bool Load_sprite_text_font(Tyra::Engine* engine){
    LoadSprite(&spr_font_BrianneTod12,Tyra::Vec2(0,0),Tyra::Vec2(10,17));
    LoadTexture(&spr_font_BrianneTod12,"FONTS/BRIANNETOD/12/_BrianneTod12alpha.png",engine);
    spr_font_BrianneTod12.mode = Tyra::SpriteMode::MODE_REPEAT;
    
    std::string file;
    int number = 65;

    // upper letters
    for(int i=0; i< 26;i++){
        LoadSprite(&spr_textFont[i],Tyra::Vec2(0,0),Tyra::Vec2(BriannedTod12Width[i],17),Tyra::SpriteMode::MODE_REPEAT);
        file  = "FONTS/BRIANNETOD/12/U";
        file += number; 
        file += ".PNG";
        LoadTexture(&spr_textFont[i],file.c_str(),engine);
        number++;
    }

    // low letters

    number = 97;
    for(int i=26; i< 52;i++){
        LoadSprite(&spr_textFont[i],Tyra::Vec2(0,0),Tyra::Vec2(BriannedTod12Width[i],17),Tyra::SpriteMode::MODE_REPEAT);
        file  = "FONTS/BRIANNETOD/12/";
        file += number; 
        file += ".PNG";
        LoadTexture(&spr_textFont[i],file.c_str(),engine);
        number++;
    }

    // numbers

    number = 48;
    for(int i=52; i< 62;i++){
        LoadSprite(&spr_textFont[i],Tyra::Vec2(0,0),Tyra::Vec2(BriannedTod12Width[i],17),Tyra::SpriteMode::MODE_REPEAT);
        file  = "FONTS/BRIANNETOD/12/";
        file += number; 
        file += ".PNG";
        LoadTexture(&spr_textFont[i],file.c_str(),engine);
        number++;
    }

    return true;
} 

void DrawText(std::string text, int x, int y){

    unsigned int maxLetter = text.size();   
    int spaceLetter = 1;
    int offsetX = 0;
    int offsetY = 0;

    for(unsigned int i=0; i<maxLetter;i++){
        int ascii = text[i];
        int sprPos  = ' ';

        if(ascii >= 'A' && ascii <= 'Z'){
            sprPos = ascii - 65;
        }else if(ascii >= 'a' && ascii <= 'z'){
            sprPos = ascii - 71;
        }else if(ascii >= '0' && ascii <='9'){
            sprPos = ascii + 4;
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