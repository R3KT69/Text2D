#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class text
{
private:
    TTF_Font *_font;
    string _msg;
    SDL_Color _textColor;
    SDL_Surface *_textSurface;
    SDL_Texture *_textTexture;
    SDL_Rect rect;

public:
    text(TTF_Font *font, string msg, SDL_Color textColor)
    {
        if (font == nullptr)
        {
            cout << "Error: Font is null" << endl;
        }

        _font = font;
        _msg = msg;
        _textColor = textColor;
        _textSurface = nullptr;
        _textTexture = nullptr;
    }

    ~text()
    {
        if (_textSurface)
        {
            SDL_FreeSurface(_textSurface);
            _textSurface = nullptr;
        }

        if (_textTexture)
        {
            SDL_DestroyTexture(_textTexture);
            _textTexture = nullptr;
        }
    }

    void DrawText(SDL_Renderer &renderer, int x = 0, int y = 0, string update_msg = "")
    {
        if (update_msg.empty())
        {
            update_msg = _msg;
        }

        if (_textSurface)
        {
            SDL_FreeSurface(_textSurface);
        }
        if (_textTexture)
        {
            SDL_DestroyTexture(_textTexture);
        }

        _textSurface = TTF_RenderText_Solid(_font, update_msg.c_str(), _textColor);
        if (_textSurface == nullptr)
        {
            cout << "Error: Could not create surface! SDL_ttf Error: " << TTF_GetError() << endl;
            return;
        }

        _textTexture = SDL_CreateTextureFromSurface(&renderer, _textSurface);
        if (_textTexture == nullptr)
        {
            cout << "Error: Could not create texture! SDL Error: " << SDL_GetError() << endl;
            SDL_FreeSurface(_textSurface);
            return;
        }

        rect = {x, y, _textSurface->w, _textSurface->h};
        SDL_FreeSurface(_textSurface);
        _textSurface = nullptr;

        InitText(renderer);
    }

    SDL_Texture *getTexture()
    {
        return _textTexture;
    }

    SDL_Rect getRect()
    {
        return rect;
    }

    void InitText(SDL_Renderer &renderer)
    {
        if (_textTexture)
        {
            SDL_RenderCopy(&renderer, _textTexture, nullptr, &rect);
        }
        else
        {
            cout << "Error: Texture is null" << endl;
        }
    }
};