//
// Created by sjr on 3/31/24.
//



#include "drawing.hpp"


void drawBox(int x0, int y0, int z0, int x1, int y1, int z1, CRGB color) {
    int minX = min(x0, x1);
    int minY = min(y0, y1);
    int minZ = min(z0, z1);
    int maxX = max(x0, x1);
    int maxY = max(y0, y1);
    int maxZ = max(z0, z1);

    for(int x=minX; x<=maxX; x++) {
        for(int y=minY; y<=maxY; y++) {
            for(int z=minZ; z<=maxZ; z++) {
                leds[address(x,y,z)] = color;
            }
        }
    }
}

void drawLine(int x1, int y1, int z1, int x2, int y2, int z2, CRGB color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int dz = z2 - z1;

    int steps = max(abs(dx), max(abs(dy), abs(dz))); // Maximum difference determines the steps

    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;
    float zIncrement = dz / (float) steps;

    float x = x1;
    float y = y1;
    float z = z1;

    for (int i = 0; i <= steps; i++) {
        // Printing the current point

        leds[address(int(round(x)), int(round(y)),int(round(z)))] = color;


        x += xIncrement;
        y += yIncrement;
        z += zIncrement;


    }

}


void clearLayers(int minLayer, int maxLayer) {
    drawBox(0,0,minLayer,8,8,maxLayer, CRGB::Black);
}



void drawPoint(int x, int y, int z, CRGB color) {
    int a = address(x, y, z);
    if (a >= 0 && a < NUM_LEDS) {
        leds[a] = color;
    }

}

void drawPoint(float x, float y, float z, CRGB color) {
    // For each of the 8 neighboring points, calculate their addresses
    // and the proportion of the color they should receive based on
    // the fractional parts of the x, y, and z coordinates.

    int baseX = (int)x;
    int baseY = (int)y;
    int baseZ = (int)z;

    // sprintf(buffer, "Direct Color Request: (%d,%d,%d -> (0x%x)", baseX, baseY, baseZ, color & 0xFFFFFF);
    // Serial.println(buffer);

    float fracX = x - baseX;
    float fracY = y - baseY;
    float fracZ = z - baseZ;

    for (int ix = 0; ix <= 1; ix++) {
        for (int iy = 0; iy <= 1; iy++) {
            for (int iz = 0; iz <= 1; iz++) {
                int adjX = baseX + ix;
                int adjY = baseY + iy;
                int adjZ = baseZ + iz;

                // Calculate the brightness factor based on distance from the original fractional coordinate
                float factor = (ix ? fracX : 1 - fracX) * (iy ? fracY : 1 - fracY) * (iz ? fracZ : 1 - fracZ);

                int a = address(adjX, adjY, adjZ);




                if (a >= 0 && a < NUM_LEDS) {
                    CRGB adjustedColor = color;
                    adjustedColor.nscale8_video((uint8_t)(factor * 255));
                    // sprintf(buffer, "Color: (%d,%d,%d -> (0x%x)", adjX, adjY, adjZ, adjustedColor);
                    // Serial.println(buffer);
                    leds[a] += adjustedColor; // Blend with existing color
                }
            }
        }
    }
}

