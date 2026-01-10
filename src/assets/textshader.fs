#version 330

#define CHARACTER_AMOUNT %char_amount%

// Character map size(in characters)

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D characters;
uniform vec4 colDiffuse;

// Character size(in pixels)
uniform int CHAR_WIDTH;
uniform int CHAR_HEIGHT;

// Display size(in characters)
uniform int DISPLAY_WIDTH;
uniform int DISPLAY_HEIGHT;

uniform int text_characters[CHARACTER_AMOUNT];
// Output fragment color
out vec4 finalColor;

// NOTE: Add your custom variables here

vec2 character2offset(int character) {
    int width = textureSize(characters, 0).x / CHAR_WIDTH;
    return vec2(mod(character, width), character / width) * vec2(CHAR_WIDTH, CHAR_HEIGHT); // DIVISION BY INT REMINDER
}

void main()
{
    vec2 character_pos = fragTexCoord * vec2(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    int character_id = text_characters[int(floor(character_pos.x)) + int(floor(character_pos.y) * DISPLAY_WIDTH)];
//     int character_id = 40;
//     int character_id = 60;
    vec2 character_uv = mod(fragTexCoord * vec2(DISPLAY_WIDTH * CHAR_WIDTH, DISPLAY_HEIGHT * CHAR_HEIGHT), vec2(CHAR_WIDTH, CHAR_HEIGHT));

    vec4 character_color = texture(characters, (character2offset(character_id) + character_uv) / vec2(textureSize(characters, 0)));
    vec2 cp_screen = character_uv / vec2(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    finalColor = character_color;
//     finalColor = vec4(fragTexCoord.x, fragTexCoord.y, 0, 1);
}
