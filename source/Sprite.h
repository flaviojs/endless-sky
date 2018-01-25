/* Sprite.h
Copyright (c) 2014 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/

#ifndef SPRITE_H_
#define SPRITE_H_

#include "Mask.h"
#include "Point.h"

#include <cstdint>
#include <string>
#include <vector>

class ImageBuffer;



// Class representing a drawable sprite. A sprite can have multiple frames, for
// animation. Certain sprites will also include a "mask" that can be used to
// check whether something has collided with them. Each frame is stored in a
// separate OpenGL texture object. This may not be as efficient as sprite
// sheets, but with modern graphics cards it will not matter much and it makes
// working with the graphics a lot simpler.
class Sprite {
public:
	explicit Sprite(const std::string &name = "");
	
	const std::string &Name() const;
	
	// Upload the given frames. The given buffer will be cleared afterwards.
	void AddFrames(ImageBuffer &buffer, bool is2x);
	// Move the given masks into this sprite's internal storage. The given
	// vector will be cleared.
	void AddMasks(std::vector<Mask> &masks);
	// Generate a texture with distances to the mask.
	// The values are normalized based on the length of corner->center.
	void GenerateMaskTexture();
	// Free up all textures loaded for this sprite.
	void Unload();
	
	// Image dimensions, in pixels.
	float Width() const;
	float Height() const;
	// Number of frames in the animation. If high DPI frames exist, the code has
	// ensured that they have the same number of frames.
	int Frames() const;
	
	// Get the offset of the center from the top left corner; this is for easy
	// shifting of corner to center coordinates.
	Point Center() const;
	
	// Get the texture index, based on whether the screen is high DPI or not.
	uint32_t Texture() const;
	// Get the index of the texture for the given high DPI mode.
	uint32_t Texture(bool isHighDPI) const;
	// Get the index of the texture with signed distances to the mask.
	uint32_t MaskTexture() const;
	// Get the collision mask for the given frame of the animation.
	const Mask &GetMask(int frame = 0) const;
	
	
private:
	std::string name;
	
	uint32_t texture[3] = {0, 0, 0};
	std::vector<Mask> masks;
	
	float width = 0.f;
	float height = 0.f;
	int frames = 0;
};



#endif
