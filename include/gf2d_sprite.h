#ifndef __GF2D_SPRITE_H__
#define __GF2D_SPRITE_H__

/**
 * gf2d_sprite
 * @license The MIT License (MIT)
   @copyright Copyright (c) 2019 EngineerOfLies
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gfc_text.h"

#include "gf3d_pipeline.h"
#include "gf3d_texture.h"

typedef struct
{
    Uint8                       _inuse;
    TextLine                    filename;               /**<the name of the file used to create the sprite*/
    Uint32                      frameCount;             /**<how many frames are loaded for this model*/
    Texture                    *texture;                /**<texture memory pointer*/
    Uint8                       framesPerLine;          /**<how many frames are per line in the sprite sheet*/
    Uint32                      frameWidth,frameHeight; /*<the size, in pixels, of the individual sprite frames*/
    VkBuffer                    buffer;
    VkDeviceMemory              bufferMemory;
    VkDescriptorSet            *descriptorSet;          /**<descriptor sets used for this sprite to render*/
}Sprite;

/**
 * @brief initialize the internal management system for sprites, auto-cleaned up on program exit
 * @param max_sprites how many concurrent sprites to support
 */
void gf2d_sprite_manager_init(Uint32 max_sprites);

/**
 * @brief loads a sprite sheet into memory
 * @param filename the name of the file containing the image data
 * @param frame_width how wide an individual frame is on the sprite sheet.  if <= 0 this is assumed to be the image size
 * @param frame_height how high an individual frame is on the sprite sheet.  if <= 0 this is assumed to be the image size
 * @param frames_per_line how many frames across are on the sprite sheet
 * @return NULL on error (check logs) or a pointer to a sprite that can be draw to the 2d overlay
 */
Sprite * gf2d_sprite_load(const char * filename,int frame_width,int frame_height, Uint32 frames_per_line);

/**
 * @brief loads a flat image into memory
 * @param filename the name of the file containing the image data
 * @return NULL on error (check logs) or a pointer to a sprite that can be draw to the 2d overlay
 */
Sprite * gf2d_sprite_load_image(const char * filename);

/**
 * @brief create a sprite from an SDL_Surface
 * @param surface pointer to SDL_Surface image data
 * @param frame_width how wide an individual frame is on the sprite sheet.  if <= 0 this is assumed to be the image size
 * @param frame_height how high an individual frame is on the sprite sheet.  if <= 0 this is assumed to be the image size
 * @param frames_per_line how many frames across are on the sprite sheet
 * @return NULL on error (check logs) or a pointer to a sprite that can be draw to the 2d overlay
 */
Sprite * gf2d_sprite_from_surface(SDL_Surface *surface,int frame_width,int frame_height, Uint32 frames_per_line);

/**
 * @brief free a previously loaded sprite
 * @param sprite a pointer to the sprite to be freed
 */
void gf2d_sprite_free(Sprite *sprite);

/**
 * @brief draw a sprite to the screen with NULLable options
 * @param sprite the sprite to draw
 * @param position here on the screen to draw it
 * @param scale (optional) if you want to scale the sprite
 * @param center (optional) the center point for scaling and rotating
 * @param rotation (optional) the angle in radians to rotate
 * @param flip (optional) set to 1 if you want to flip in the horizontal,vertical axis
 * @param colorShift (optional) if you want to gamma shift the sprite or set an alpha value
 * @param clip (optional) if you want to crop the image (pixels from left, pixels from top, pixels from right, pixels from bottom)
 * @param frame which frame to draw
 */
void gf2d_sprite_draw(
    Sprite * sprite,
    Vector2D position,
    Vector2D * scale,
    Vector2D * center,
    float    * rotation,
    Vector2D * flip,
    Color    * colorShift,
    Vector4D * clip,
    Uint32 frame);

/**
 * @brief draw a sprite to the screen
 * @param sprite the sprite to draw
 * @param position here on the screen to draw it
 * @param scale scale the sprite (1,1) for no scale
 * @param center the center point for scaling and rotating (0,0) for top left
 * @param rotation the angle in radians to rotate
 * @param flip set to 1 if you want to flip in the horizontal,vertical axis (0,0) is no flip
 * @param colorShift color mod gfc_color(1,1,1,1) for no change
 * @param clip if you want to crop the image (pixels from left, pixels from top, pixels from right, pixels from bottom)
 * @param frame which frame to draw
 */
void gf2d_sprite_draw_full(
    Sprite   * sprite,
    Vector2D   position,
    Vector2D   scale,
    Vector2D   center,
    float      rotation,
    Vector2D   flip,
    Color      colorShift,
    Vector4D   clip,
    Uint32     frame);

/**
 * @brief draw a sprite to the screen
 * @param sprite the sprite to draw
 * @param position here on the screen to draw it
 * @param frame which frame to draw
 */
void gf2d_sprite_draw_simple(
    Sprite   * sprite,
    Vector2D   position,
    Uint32     frame);

/**
 * @brief get the default pipeline for overlay rendering
 * @return NULL on error or not yet initlialized, the pipeline otherwise
 */
Pipeline *gf2d_sprite_get_pipeline();

/**
 * @brief get the binding description for a sprite
 */
VkVertexInputBindingDescription * gf2d_sprite_get_bind_description();

VkVertexInputAttributeDescription * gf2d_sprite_get_attribute_descriptions(Uint32 *count);

/**
 * @brief needs to be called once at the beginning of each render frame
 */
void gf3d_sprite_reset_pipes();

/**
 * @brief called to submit all draw commands to the sprite pipelines
 */
void gf3d_sprite_submit_pipe_commands();


#endif
