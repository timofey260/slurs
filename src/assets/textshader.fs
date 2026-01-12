#version 330

#define CHARACTER_AMOUNT %char_amount%
#define PALETTE_SIZE 256
#define PAIR_SIZE 256

// Character map size(in characters)

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D characters;
uniform vec4 colDiffuse;

// Character size(in pixels)
uniform ivec2 CHAR_SIZE;
// Display size(in characters)
uniform ivec2 DISPLAY_SIZE;

uniform ivec2 text_characters[CHARACTER_AMOUNT];
uniform ivec3 colors[PALETTE_SIZE];
uniform ivec2 color_pairs[PAIR_SIZE];

uniform vec3 palette[PALETTE_SIZE];
// Output fragment color
out vec4 finalColor;

// NOTE: Add your custom variables here

vec2 character2offset(int character) {
    int width = textureSize(characters, 0).x / CHAR_SIZE.x;
    return vec2(mod(character, width), character / width) * vec2(CHAR_SIZE.x, CHAR_SIZE.y); // DIVISION BY INT REMINDER
}

void main()
{
    vec2 character_pos = fragTexCoord * vec2(DISPLAY_SIZE.x, DISPLAY_SIZE.y);
    int character_index = int(floor(character_pos.x)) + int(floor(character_pos.y) * DISPLAY_SIZE.x);
    int character_id = text_characters[character_index].x;
    int character_attr = text_characters[character_index].y;
//     int character_id = 40;
//     int character_id = 60;
    vec2 character_uv = mod(fragTexCoord * vec2(DISPLAY_SIZE.x * CHAR_SIZE.x, DISPLAY_SIZE.y * CHAR_SIZE.y), vec2(CHAR_SIZE.x, CHAR_SIZE.y));
    ivec2 char_color_pair = color_pairs[character_attr & 0xff];
    vec3 color_fg = vec3(vec3(colors[char_color_pair.x]) / 255.0);
    vec3 color_bg = vec3(vec3(colors[char_color_pair.y]) / 255.0);

    vec4 character_color = texture(characters, (character2offset(character_id) + character_uv) / vec2(textureSize(characters, 0)));
    vec2 cp_screen = character_uv / vec2(DISPLAY_SIZE.x, DISPLAY_SIZE.y);

    float color_threshold = step(0.5, character_color.r);
    vec3 character_brightness = color_bg * (1.0 - color_threshold) + color_fg * color_threshold;

    finalColor = vec4(character_brightness, 1.0);
//     finalColor = vec4(fragTexCoord.x, fragTexCoord.y, 0, 1);
}
