/**
 * @file test_helpers.cpp
 * @author Daniel Reeves (dtr@vt.edu)
 * @brief function test cases for the system and stuff
 * @version 0.1
 * @date 2025-04-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "FSM.h"
#include <unity.h>

#define NUM_DATA_POINTS 100
#define LORA_TESTS 0

uint8_t image_data[] PROGMEM = {
    0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46, 0x00, 0x01, 0x01, 0x01, 0x00, 0x60,
    0x00, 0x60, 0x00, 0x00, 0xFF, 0xDB, 0x00, 0x43, 0x00, 0x14, 0x0E, 0x0F, 0x12, 0x0F, 0x0D, 0x14,
    0x12, 0x11, 0x12, 0x17, 0x16, 0x14, 0x18, 0x1F, 0x33, 0x21, 0x1F, 0x1C, 0x1C, 0x1F, 0x3F, 0x2D,
    0x2F, 0x25, 0x33, 0x4A, 0x41, 0x4E, 0x4D, 0x49, 0x41, 0x48, 0x46, 0x52, 0x5C, 0x76, 0x64, 0x52,
    0x57, 0x6F, 0x58, 0x46, 0x48, 0x66, 0x8C, 0x68, 0x6F, 0x7A, 0x7D, 0x84, 0x85, 0x84, 0x4F, 0x63,
    0x91, 0x9B, 0x8F, 0x80, 0x9A, 0x76, 0x81, 0x84, 0x7F, 0xFF, 0xDB, 0x00, 0x43, 0x01, 0x16, 0x17,
    0x17, 0x1F, 0x1B, 0x1F, 0x3C, 0x21, 0x21, 0x3C, 0x7F, 0x54, 0x48, 0x54, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xC0,
    0x00, 0x11, 0x08, 0x00, 0xC0, 0x00, 0x90, 0x03, 0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11,
    0x01, 0xFF, 0xC4, 0x00, 0x1A, 0x00, 0x00, 0x02, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x01, 0x02, 0x05, 0x00, 0x06, 0xFF, 0xC4, 0x00,
    0x38, 0x10, 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x05, 0x02, 0x03, 0x08, 0x02, 0x01, 0x05, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x11, 0x21, 0x04, 0x12, 0x31, 0x41, 0x51, 0x05, 0x13, 0x22,
    0x61, 0x71, 0x32, 0x81, 0x14, 0x91, 0xA1, 0x23, 0x42, 0x52, 0xB1, 0xC1, 0xD1, 0xE1, 0xF0, 0x33,
    0xF1, 0x24, 0x06, 0x15, 0x25, 0x62, 0x72, 0xFF, 0xC4, 0x00, 0x19, 0x01, 0x00, 0x03, 0x01, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x00,
    0x04, 0x05, 0xFF, 0xC4, 0x00, 0x21, 0x11, 0x00, 0x02, 0x02, 0x03, 0x00, 0x02, 0x03, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x11, 0x03, 0x21, 0x31, 0x12, 0x32,
    0x22, 0x41, 0x51, 0x13, 0x61, 0xFF, 0xDA, 0x00, 0x0C, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11,
    0x00, 0x3F, 0x00, 0x26, 0xA5, 0x00, 0x70, 0xF6, 0xB4, 0xA1, 0x83, 0x37, 0x97, 0xC1, 0xB8, 0xC6,
    0x7F, 0xA5, 0x57, 0x4E, 0x57, 0x55, 0xA3, 0x47, 0x04, 0xA6, 0xC6, 0xF4, 0xA9, 0x38, 0x02, 0xFC,
    0xDE, 0xB4, 0xE6, 0xD0, 0xA6, 0xC4, 0x73, 0x1E, 0xFF, 0x00, 0x2E, 0x35, 0x2B, 0xB4, 0x1B, 0x92,
    0x38, 0xC0, 0xFB, 0x52, 0xF2, 0xE9, 0xA1, 0xD2, 0xE9, 0xE1, 0x4B, 0x93, 0x2C, 0x9F, 0x51, 0x0C,
    0x05, 0xFB, 0x8E, 0xDC, 0x9E, 0x2A, 0x52, 0x8D, 0x23, 0x21, 0xCD, 0x1E, 0x98, 0xAC, 0x96, 0x2F,
    0xB8, 0x0B, 0x00, 0xDD, 0x58, 0x0B, 0xD2, 0xFA, 0xA5, 0xF2, 0xB5, 0x5B, 0x8E, 0xD7, 0x01, 0x8A,
    0xAB, 0x16, 0xB5, 0xB1, 0x7E, 0xB5, 0x5D, 0x5F, 0x9A, 0xB1, 0x21, 0x8C, 0x90, 0x41, 0x0A, 0xAA,
    0x06, 0x70, 0x6F, 0xFD, 0x29, 0x73, 0xA9, 0x8C, 0x40, 0xEC, 0x21, 0x66, 0x65, 0x20, 0xBC, 0x8D,
    0x9B, 0xB1, 0xE0, 0x0F, 0x6C, 0x50, 0xA4, 0xC6, 0x16, 0x4D, 0x5B, 0x02, 0xCC, 0xF1, 0x2B, 0x99,
    0x32, 0xD7, 0x1E, 0xAF, 0xF7, 0xFB, 0x55, 0xF4, 0xAE, 0x06, 0xB2, 0x27, 0x79, 0x63, 0x8E, 0x37,
    0xE2, 0x25, 0x3B, 0x9B, 0xEE, 0x7A, 0x71, 0x45, 0x8F, 0x47, 0xA2, 0x98, 0x33, 0xB1, 0x3B, 0x0D,
    0xAC, 0x49, 0xC0, 0x37, 0xCF, 0xE5, 0xFC, 0xA9, 0x2D, 0x3B, 0x47, 0x19, 0x66, 0x04, 0x79, 0x3B,
    0xF6, 0xDA, 0xD9, 0xE0, 0xE6, 0xB2, 0x88, 0x0D, 0x03, 0xBE, 0x2D, 0x43, 0xC9, 0x0D, 0xE5, 0x55,
    0x62, 0x53, 0x79, 0x17, 0xCE, 0x3A, 0x57, 0x6B, 0x66, 0x69, 0x82, 0x42, 0xE9, 0xB0, 0xB1, 0xDE,
    0xC4, 0x71, 0xFE, 0x7A, 0xD0, 0xA2, 0x99, 0x80, 0x55, 0x88, 0x93, 0x67, 0x1B, 0x58, 0x8E, 0x7E,
    0xD5, 0xA7, 0xAA, 0x45, 0x90, 0x19, 0xFC, 0xAF, 0x35, 0xAC, 0x40, 0x5D, 0xDF, 0x4A, 0xF5, 0xFB,
    0xD3, 0x2E, 0x18, 0xCF, 0x8A, 0x38, 0x34, 0xE2, 0xE5, 0x2D, 0x62, 0xBB, 0x64, 0xBD, 0xC8, 0x27,
    0x9C, 0x75, 0xA3, 0x4F, 0x21, 0x7D, 0x33, 0xEA, 0x56, 0x32, 0xA9, 0x85, 0x62, 0xC6, 0xD8, 0xF6,
    0xF6, 0x34, 0x2D, 0x66, 0x96, 0x63, 0x14, 0x7A, 0x81, 0x66, 0x2E, 0x32, 0x40, 0x23, 0x67, 0x60,
    0x2A, 0xAB, 0x21, 0xD6, 0x41, 0xB2, 0x67, 0x22, 0x25, 0x37, 0x61, 0x6E, 0x33, 0x6B, 0x5F, 0xAF,
    0xC5, 0x67, 0xDD, 0x98, 0xA4, 0x0D, 0x32, 0xE9, 0x1A, 0x35, 0xC1, 0x88, 0x12, 0x5A, 0xF8, 0xCF,
    0xF2, 0xE6, 0x92, 0x9E, 0x67, 0xD4, 0x60, 0x9B, 0x13, 0x65, 0x01, 0x78, 0xB7, 0xC5, 0x6E, 0x68,
    0x62, 0x49, 0x34, 0xFA, 0xA7, 0x31, 0x0B, 0x09, 0x4E, 0x2F, 0x7C, 0x0E, 0x94, 0xAC, 0x9A, 0x05,
    0x3E, 0x26, 0x52, 0x34, 0x03, 0x0A, 0x6D, 0xF6, 0xA3, 0xE3, 0xAB, 0x35, 0x99, 0xDF, 0x87, 0x5D,
    0x34, 0x33, 0xAB, 0x59, 0x9D, 0x80, 0x00, 0x9E, 0x86, 0xF9, 0xFB, 0xD3, 0x09, 0xE4, 0x7F, 0xED,
    0xD1, 0xCF, 0x2A, 0x1B, 0xC6, 0x4C, 0x63, 0x6F, 0x51, 0xD7, 0xE2, 0xA9, 0xA8, 0xD2, 0xAC, 0x5A,
    0x90, 0x15, 0xF7, 0x2C, 0x64, 0x6F, 0x62, 0x6F, 0x6F, 0x6A, 0x1E, 0xB8, 0x34, 0x3A, 0xAD, 0x56,
    0x9B, 0x3E, 0x5B, 0xB7, 0x9A, 0x8A, 0x38, 0xCD, 0x13, 0x0A, 0xEE, 0x2C, 0xE5, 0xF0, 0x00, 0xE3,
    0xE2, 0xD4, 0xC7, 0x85, 0xC5, 0x76, 0x42, 0x43, 0x02, 0x5C, 0xE4, 0x0F, 0x6F, 0xF3, 0x54, 0x65,
    0x8E, 0x38, 0xAC, 0xAD, 0x72, 0x4E, 0xDB, 0x5A, 0xB4, 0x3C, 0x14, 0x32, 0xC9, 0xB5, 0x55, 0x98,
    0x01, 0xEA, 0xEC, 0xA4, 0x9E, 0x47, 0xDA, 0xD4, 0x3A, 0x16, 0x6B, 0xEB, 0x0B, 0x45, 0x08, 0x2A,
    0x37, 0x39, 0x1B, 0x6F, 0xCE, 0x7B, 0xD6, 0x17, 0x8B, 0xC2, 0xE8, 0xDA, 0x76, 0x61, 0xEA, 0x72,
    0xD8, 0xF6, 0xC5, 0x6B, 0x6A, 0x35, 0x4D, 0x36, 0xA5, 0xB4, 0xDB, 0x18, 0xC4, 0x45, 0x89, 0x4E,
    0x86, 0xB1, 0xFC, 0x66, 0x49, 0x3F, 0x11, 0x0A, 0x48, 0x6C, 0xB1, 0x0B, 0x04, 0xB7, 0x7F, 0xFA,
    0xA6, 0x75, 0x62, 0x23, 0x4B, 0xC4, 0xDB, 0xCB, 0x95, 0x34, 0xC8, 0xB2, 0x28, 0x58, 0xC9, 0x13,
    0x06, 0xCB, 0xF7, 0xA4, 0x44, 0xC2, 0x59, 0x6D, 0x28, 0x93, 0xCB, 0x46, 0xCA, 0xBA, 0x96, 0x2B,
    0x7E, 0xFF, 0x00, 0xDE, 0x8B, 0xE2, 0x7A, 0x91, 0xA9, 0xD6, 0xB8, 0x6F, 0x32, 0x31, 0x10, 0xB2,
    0xDA, 0xC0, 0xEE, 0xEE, 0x41, 0xF7, 0xC5, 0x67, 0x7E, 0x22, 0x59, 0xDA, 0x2F, 0x32, 0x42, 0xC4,
    0x35, 0xB7, 0x58, 0x5F, 0xB5, 0xBE, 0x29, 0x5A, 0xB0, 0x9B, 0x06, 0x61, 0xAA, 0xD3, 0x3C, 0x3A,
    0x5B, 0x95, 0x56, 0xB1, 0x66, 0x62, 0x49, 0x16, 0xB8, 0x1F, 0xEF, 0x6A, 0x29, 0xD3, 0xA1, 0x40,
    0xB2, 0xC4, 0x2F, 0x21, 0x55, 0xF4, 0x93, 0xF4, 0xE4, 0x10, 0x0F, 0xB5, 0x89, 0xAC, 0x88, 0xF5,
    0x12, 0x69, 0x35, 0x0E, 0x61, 0xFA, 0xDA, 0xE0, 0xAF, 0x5C, 0xF2, 0x00, 0xE8, 0x69, 0xFD, 0x6C,
    0xD2, 0x91, 0x1C, 0x0B, 0xB2, 0x2D, 0x98, 0x0A, 0xAD, 0x72, 0x71, 0x7C, 0xF6, 0x18, 0xE2, 0x87,
    0x02, 0x2F, 0xAC, 0x95, 0xF4, 0xAD, 0x34, 0x2B, 0xE9, 0x50, 0xF6, 0xE0, 0x0B, 0x01, 0xC6, 0x29,
    0x05, 0x61, 0xE5, 0x2D, 0xF1, 0xEA, 0xE0, 0x51, 0xE5, 0x77, 0x74, 0x12, 0x6F, 0x2D, 0xBC, 0xD9,
    0xB7, 0x0C, 0x83, 0xFD, 0x69, 0x77, 0xB3, 0x4A, 0xA0, 0x1D, 0xA2, 0xD8, 0x1D, 0xAB, 0x51, 0x86,
    0x74, 0xCC, 0xB2, 0x84, 0x45, 0xDC, 0x24, 0x0D, 0x9B, 0x0C, 0x11, 0xD0, 0xFC, 0xD3, 0xC9, 0x3B,
    0x68, 0x91, 0x67, 0x90, 0x9D, 0x99, 0x1B, 0x59, 0xBE, 0xAE, 0xF8, 0x14, 0x86, 0x97, 0x62, 0xEB,
    0x90, 0x38, 0xFD, 0x98, 0x37, 0x6B, 0x0E, 0xD5, 0xA6, 0x74, 0xAA, 0xCC, 0x24, 0x99, 0x41, 0x6E,
    0x42, 0xF4, 0x5A, 0x35, 0x6C, 0x29, 0x10, 0x9E, 0x3A, 0xB3, 0x0D, 0xAF, 0xA7, 0x9B, 0x68, 0xE1,
    0x91, 0xAC, 0x7F, 0x95, 0x46, 0x97, 0x55, 0xA1, 0x47, 0x2D, 0x22, 0xBD, 0x87, 0xD2, 0xA4, 0x5F,
    0x3D, 0x6F, 0x4C, 0x05, 0xB0, 0xC0, 0xB0, 0xA0, 0x4F, 0xA2, 0x4D, 0x40, 0xB8, 0xF4, 0x3F, 0xF1,
    0x01, 0x47, 0xA1, 0xF1, 0x35, 0xB4, 0x0B, 0x19, 0xD1, 0xDE, 0x38, 0x42, 0x2B, 0xE7, 0x6D, 0x0B,
    0xC4, 0x64, 0x8B, 0x4F, 0x03, 0x4D, 0x60, 0x64, 0x5B, 0x32, 0x77, 0x1D, 0x2B, 0xCF, 0x8D, 0x5C,
    0xFA, 0x09, 0x0C, 0x32, 0x82, 0xC0, 0x7D, 0x36, 0x62, 0x3E, 0xE2, 0x87, 0xA8, 0x7D, 0x44, 0xCE,
    0x5A, 0x79, 0x0F, 0x97, 0xB4, 0xDA, 0xDF, 0x1D, 0xA8, 0xDD, 0x0B, 0x47, 0x19, 0x5A, 0x47, 0x77,
    0x07, 0x6A, 0xB3, 0x6E, 0xE7, 0x9A, 0xAA, 0xB1, 0x97, 0x51, 0xBD, 0xD8, 0x99, 0x31, 0x77, 0x3D,
    0x2A, 0xFA, 0x5C, 0x1B, 0x14, 0x0C, 0x6E, 0x71, 0x6E, 0x96, 0xE9, 0x41, 0x85, 0x48, 0xDF, 0x21,
    0x60, 0x0F, 0x19, 0xED, 0x4A, 0x12, 0xEF, 0x11, 0x57, 0x08, 0xED, 0xC1, 0x39, 0xEF, 0xEF, 0x5A,
    0x3E, 0x18, 0x7C, 0xA9, 0x1D, 0x05, 0xD0, 0xAA, 0x13, 0xF7, 0xAC, 0xF9, 0x3D, 0x30, 0x97, 0x23,
    0x17, 0xED, 0xFA, 0x56, 0x87, 0x84, 0x4C, 0x1F, 0xC4, 0x64, 0x90, 0xFD, 0x2E, 0xA4, 0xD8, 0x0E,
    0xC2, 0x82, 0xE9, 0x9F, 0x06, 0x35, 0x1A, 0x99, 0x74, 0xB3, 0x32, 0xAE, 0xD7, 0x92, 0x5B, 0x62,
    0xDC, 0x1F, 0xF6, 0xD5, 0x8B, 0xE3, 0x8B, 0xFF, 0x00, 0xC9, 0x92, 0x09, 0xB9, 0x55, 0x2D, 0xBB,
    0xA1, 0xAF, 0x43, 0xAA, 0x9F, 0x0C, 0x76, 0xED, 0x6C, 0x1D, 0xF7, 0xBD, 0x96, 0xFD, 0xAB, 0xCB,
    0xF8, 0x83, 0x32, 0xEA, 0xE7, 0x57, 0x2C, 0x5B, 0x70, 0x17, 0x27, 0x23, 0xD8, 0xD3, 0xB7, 0xB1,
    0x62, 0x3D, 0xE2, 0x31, 0xC8, 0xDA, 0x99, 0x5A, 0x43, 0x7B, 0x12, 0x17, 0x71, 0xCB, 0x5A, 0xDF,
    0xDE, 0x86, 0x9E, 0x1E, 0x64, 0x95, 0x82, 0x38, 0x23, 0xCB, 0xDE, 0x2D, 0xD4, 0xDB, 0x8F, 0x9A,
    0x3B, 0xEA, 0x14, 0xE9, 0xC4, 0x72, 0xC8, 0xEC, 0x54, 0x92, 0xA9, 0xC8, 0x06, 0xDC, 0xDF, 0x9F,
    0xFB, 0xAB, 0xE9, 0xBC, 0xD8, 0x61, 0x33, 0xC0, 0xC1, 0x5F, 0x6D, 0x82, 0x6D, 0xE4, 0x7C, 0xFD,
    0xA9, 0x2C, 0x20, 0xC4, 0x0D, 0x0F, 0x89, 0x45, 0x12, 0x03, 0x23, 0xAD, 0x99, 0xB3, 0x6C, 0xDB,
    0x80, 0x7E, 0xD4, 0x49, 0x4A, 0xCC, 0xC4, 0x95, 0x71, 0x26, 0x58, 0x92, 0x6F, 0x43, 0x69, 0x65,
    0xF1, 0x0D, 0x62, 0x6D, 0xFA, 0xDA, 0xE2, 0xC0, 0x5B, 0x20, 0x71, 0x45, 0x97, 0x70, 0x3E, 0x51,
    0xD8, 0x36, 0x9D, 0xA4, 0x0E, 0xFF, 0x00, 0xF7, 0x41, 0xA3, 0x09, 0x80, 0x82, 0x14, 0x65, 0x24,
    0xDD, 0xB3, 0xF3, 0x40, 0x89, 0xF6, 0x6A, 0xAE, 0x2C, 0x48, 0x06, 0xD4, 0x58, 0x91, 0x84, 0x04,
    0xA8, 0xDD, 0x93, 0x6A, 0x5F, 0x70, 0xF3, 0x51, 0x92, 0xE0, 0xB1, 0xC8, 0xED, 0x4C, 0x61, 0xCD,
    0x1B, 0x1F, 0xC5, 0x23, 0x95, 0x24, 0x12, 0x05, 0xAD, 0x7E, 0xA3, 0xFC, 0xD6, 0x9C, 0xDE, 0x20,
    0x82, 0x5B, 0x34, 0x52, 0xAA, 0x93, 0xF5, 0x32, 0xD8, 0x52, 0xDA, 0x48, 0x48, 0x8D, 0x1A, 0x37,
    0xDB, 0x29, 0xBE, 0xDB, 0xF0, 0x7D, 0xBF, 0xDE, 0xF4, 0x5D, 0x44, 0x46, 0x72, 0x03, 0x0D, 0xB6,
    0xC1, 0x6B, 0xDB, 0x1F, 0x6A, 0x29, 0xAA, 0x19, 0x59, 0xD3, 0x6B, 0xED, 0xFF, 0x00, 0x02, 0x89,
    0xAC, 0x32, 0x54, 0xE0, 0x7D, 0xEA, 0xF0, 0xEB, 0x0E, 0xE5, 0x13, 0xA0, 0x8C, 0x31, 0xB0, 0x24,
    0xE2, 0xFF, 0x00, 0x34, 0x19, 0x22, 0x5B, 0xB2, 0xC4, 0x17, 0x63, 0x58, 0x15, 0x06, 0xD6, 0x23,
    0x8A, 0xE4, 0xD2, 0x06, 0x51, 0x1B, 0x46, 0xAA, 0x97, 0x04, 0xE6, 0xF7, 0xA2, 0x35, 0x31, 0x3F,
    0x1C, 0x0C, 0x9A, 0x91, 0x7C, 0x82, 0x2F, 0x50, 0xA0, 0xBE, 0x90, 0x39, 0xBE, 0xE1, 0x9B, 0xF4,
    0xB7, 0x5A, 0x2F, 0x8C, 0xC7, 0x34, 0xDA, 0x98, 0x91, 0x1B, 0x7B, 0x32, 0xDB, 0xD4, 0x07, 0xE7,
    0x7A, 0x32, 0x78, 0x50, 0x7D, 0x1C, 0x6C, 0xD3, 0xC9, 0x90, 0x47, 0xA4, 0xD9, 0x47, 0x7C, 0x1A,
    0x59, 0x34, 0x90, 0xB4, 0xC1, 0x69, 0xD2, 0x44, 0x86, 0x56, 0x28, 0x57, 0x70, 0xF5, 0x92, 0x2D,
    0x83, 0xDA, 0x85, 0x13, 0xAC, 0x49, 0x23, 0x46, 0x37, 0x2B, 0x0B, 0x02, 0xC2, 0xFB, 0x73, 0xCD,
    0x46, 0xAC, 0xCA, 0x81, 0xD2, 0x59, 0x1A, 0x62, 0x9E, 0x95, 0xF7, 0xF7, 0xA6, 0xD1, 0xB4, 0xD2,
    0xF8, 0x73, 0xC8, 0x88, 0xCA, 0xAA, 0x3C, 0xBB, 0x1E, 0x6F, 0x4A, 0x62, 0x3C, 0x45, 0x04, 0x9A,
    0x4D, 0x3B, 0xAD, 0xCD, 0xDA, 0xC7, 0xD8, 0xD5, 0x7C, 0x12, 0x3D, 0xFE, 0x27, 0x1A, 0x96, 0x23,
    0x62, 0x12, 0x07, 0x7F, 0x6A, 0xA8, 0x7F, 0xFC, 0x65, 0x86, 0xFB, 0x55, 0x6E, 0xD7, 0x27, 0x02,
    0xC6, 0xA3, 0x4B, 0xA8, 0x44, 0xF1, 0x40, 0xF1, 0x90, 0xAA, 0x2E, 0x10, 0x9F, 0xEB, 0x45, 0x01,
    0x9B, 0xDE, 0x22, 0x09, 0xF0, 0xE9, 0xC6, 0xD0, 0x4E, 0xD3, 0x60, 0x4D, 0xAE, 0xBD, 0xEB, 0xC5,
    0xCD, 0x0B, 0x29, 0x20, 0xF1, 0x71, 0xB7, 0xE2, 0xBD, 0x0F, 0x88, 0x6B, 0xA5, 0xFD, 0xA2, 0x38,
    0x42, 0xCC, 0x2D, 0x70, 0x2C, 0x40, 0x3D, 0x3F, 0x2A, 0xC4, 0x97, 0x71, 0x39, 0x1C, 0x30, 0xB1,
    0xA6, 0x4E, 0xC0, 0xB4, 0x69, 0xCB, 0xA5, 0x72, 0x1C, 0xED, 0x60, 0x5E, 0xE5, 0x40, 0xFE, 0x1E,
    0x41, 0xA2, 0xEA, 0xA1, 0x68, 0x20, 0x84, 0xED, 0x6D, 0x85, 0x6D, 0x83, 0x9B, 0x8E, 0xE3, 0xEF,
    0x56, 0x93, 0x52, 0xD2, 0xEA, 0x3C, 0xDD, 0xC5, 0x63, 0x3E, 0x90, 0x14, 0xE0, 0xF4, 0xBD, 0x03,
    0x50, 0xEB, 0x1E, 0x9A, 0x10, 0x1E, 0xE6, 0x41, 0xEB, 0xB3, 0x12, 0x5C, 0xF4, 0x27, 0xA6, 0x29,
    0x29, 0x18, 0x06, 0x96, 0x66, 0x8B, 0x55, 0x1B, 0x81, 0x91, 0x77, 0x37, 0xFD, 0xEC, 0xF1, 0x4F,
    0xA9, 0x33, 0xF9, 0xCE, 0xC0, 0xA9, 0x37, 0x7B, 0xDB, 0xFD, 0xEB, 0x59, 0x44, 0xEC, 0x7B, 0x1C,
    0xE2, 0xC4, 0xF6, 0xF7, 0xA7, 0xA0, 0x9E, 0x4F, 0xC2, 0x83, 0xEA, 0x11, 0x8B, 0x96, 0x28, 0xB7,
    0x24, 0x5F, 0xF4, 0xA3, 0x27, 0x48, 0xC5, 0x1C, 0xC4, 0x9A, 0x14, 0x55, 0xDC, 0x25, 0x5F, 0xAB,
    0x38, 0x1D, 0x3F, 0xAD, 0x67, 0x69, 0x73, 0x28, 0xEB, 0x61, 0x6A, 0x6D, 0xC4, 0x45, 0x5F, 0x66,
    0xE6, 0x50, 0x30, 0xC7, 0x04, 0xFB, 0xD2, 0x91, 0x86, 0x49, 0x09, 0x50, 0x7D, 0x23, 0x75, 0x14,
    0x63, 0x6F, 0x4C, 0x5A, 0x24, 0x8D, 0x9E, 0x07, 0x8D, 0x19, 0xB7, 0x6F, 0x3C, 0x13, 0x6C, 0x01,
    0x53, 0xAA, 0x99, 0x08, 0xD8, 0xA3, 0x71, 0x61, 0xF6, 0xAC, 0xF5, 0xD4, 0xCB, 0x36, 0x97, 0x68,
    0x1B, 0x63, 0xB9, 0x60, 0xB9, 0xE7, 0xBF, 0x6A, 0xAE, 0x93, 0x5C, 0x51, 0x89, 0x7F, 0xA6, 0xD6,
    0xA5, 0x45, 0x23, 0xC1, 0xA0, 0x1A, 0x37, 0xDE, 0x23, 0xBE, 0x33, 0x65, 0xE6, 0x8C, 0xFA, 0xC5,
    0x11, 0xAB, 0x1C, 0x13, 0xC8, 0xA5, 0x53, 0x5D, 0x1C, 0x51, 0xB3, 0x29, 0xDC, 0xC7, 0xAD, 0x66,
    0x4D, 0xA8, 0x69, 0x1F, 0x9C, 0x5E, 0x98, 0x66, 0xCD, 0x68, 0x65, 0xFC, 0x4E, 0xB4, 0x12, 0xD6,
    0xC5, 0x81, 0xED, 0x5D, 0x2B, 0x4C, 0xF1, 0x34, 0xC6, 0x53, 0x1E, 0x8D, 0x72, 0xB6, 0xC9, 0x39,
    0xE8, 0x3D, 0xEA, 0xBE, 0x07, 0x19, 0x79, 0x5A, 0x52, 0x3D, 0x20, 0x58, 0x7B, 0xD5, 0x5E, 0x36,
    0x97, 0x4C, 0x9E, 0xB2, 0x22, 0x8C, 0x6D, 0xDB, 0xD0, 0x31, 0x34, 0x24, 0x24, 0x9F, 0xD0, 0x25,
    0x1E, 0x83, 0x23, 0x58, 0x85, 0x61, 0x72, 0x1B, 0xFC, 0x57, 0x69, 0x75, 0x17, 0x8E, 0x78, 0xC8,
    0xB2, 0x48, 0xD8, 0xF6, 0xC8, 0xFE, 0x94, 0xFC, 0x61, 0x23, 0xFC, 0x44, 0x4B, 0x01, 0x55, 0x50,
    0x6C, 0xB6, 0xBD, 0x89, 0x1C, 0xD6, 0x5C, 0x40, 0xB3, 0xB9, 0x90, 0xFA, 0xAD, 0xD0, 0x72, 0x33,
    0x9A, 0x09, 0xD8, 0xA1, 0x75, 0x6C, 0x64, 0x46, 0xF2, 0x92, 0xC8, 0x18, 0x93, 0x6E, 0xD4, 0xB4,
    0x78, 0x7C, 0xDA, 0xE3, 0x8A, 0x7E, 0x7D, 0x9F, 0x83, 0x11, 0xAE, 0xE2, 0xC0, 0x6E, 0x63, 0xD0,
    0x8A, 0x57, 0x4E, 0x81, 0xF5, 0x0A, 0xA7, 0x2B, 0x7C, 0xF4, 0xA6, 0x46, 0x67, 0x6A, 0x75, 0x2C,
    0xD1, 0xEF, 0x7C, 0xB7, 0x17, 0xA1, 0xC5, 0x79, 0x0B, 0x6E, 0xFD, 0xD3, 0x7B, 0x5B, 0x91, 0x5D,
    0xAC, 0x42, 0xC4, 0xA2, 0xA9, 0xB6, 0xFB, 0x0A, 0x22, 0x5D, 0x64, 0x1B, 0x2D, 0xB4, 0xAD, 0x9B,
    0xDF, 0x34, 0x50, 0x06, 0x65, 0x46, 0x48, 0xDC, 0x42, 0x4A, 0x15, 0xBB, 0xA5, 0xF3, 0x6B, 0x66,
    0xDF, 0xD6, 0x97, 0x33, 0x79, 0x91, 0xC1, 0x23, 0x92, 0x4F, 0xB0, 0xC0, 0x34, 0xCC, 0xEC, 0x17,
    0x4B, 0x23, 0x29, 0xDB, 0xE9, 0xF4, 0x8B, 0x71, 0x49, 0x29, 0x0B, 0x14, 0x27, 0x90, 0x39, 0xA0,
    0x80, 0x44, 0xD2, 0x59, 0x5A, 0xE9, 0xB8, 0x70, 0x41, 0xEB, 0x47, 0xD1, 0x4C, 0xAF, 0x14, 0x91,
    0x85, 0xF4, 0x91, 0x75, 0x04, 0xF1, 0x9E, 0xA7, 0xB7, 0x34, 0xBE, 0xA1, 0xAF, 0x16, 0xE5, 0x1B,
    0x41, 0xC8, 0xA0, 0x69, 0x79, 0xDA, 0x39, 0x38, 0xB7, 0xCD, 0x66, 0xAD, 0x18, 0xD3, 0xD4, 0x3B,
    0x48, 0x8C, 0xC7, 0x6D, 0xF8, 0x25, 0x46, 0x3E, 0xD4, 0x96, 0xF0, 0x03, 0x96, 0x17, 0x04, 0x01,
    0x4E, 0x45, 0x0C, 0xA7, 0x4F, 0x1A, 0xB9, 0x0A, 0xA0, 0x63, 0x70, 0xCF, 0xE5, 0x54, 0x68, 0x60,
    0x8D, 0x76, 0x9D, 0xD2, 0x37, 0xCD, 0x87, 0xE9, 0x55, 0x86, 0x19, 0x35, 0xC1, 0x5C, 0xD2, 0x14,
    0x8B, 0x55, 0x2A, 0x46, 0xC9, 0x17, 0x51, 0x6B, 0x5A, 0xF7, 0xA6, 0xDF, 0xC3, 0x19, 0xA0, 0x46,
    0x0F, 0xB5, 0x98, 0x5D, 0x94, 0x8E, 0x2A, 0xD0, 0x28, 0x0D, 0x72, 0x00, 0x5E, 0x8A, 0x38, 0xAD,
    0x6D, 0x08, 0x5D, 0x4E, 0x81, 0x37, 0x5C, 0x30, 0x24, 0x5F, 0xEF, 0xFC, 0xAA, 0x92, 0xC1, 0xE2,
    0xAC, 0xD1, 0xC9, 0x6E, 0x8F, 0x3E, 0x9E, 0x1C, 0xEB, 0xE9, 0x69, 0x40, 0x03, 0xB0, 0xA6, 0x60,
    0xF0, 0xF8, 0x95, 0xAE, 0xF7, 0x73, 0xEF, 0xC5, 0x69, 0x49, 0xA6, 0x2A, 0xE1, 0x59, 0x49, 0x27,
    0x82, 0x38, 0x34, 0xCC, 0x1A, 0x25, 0x53, 0xBA, 0x4C, 0x9F, 0xE1, 0xE9, 0x51, 0x51, 0x6D, 0xD1,
    0x67, 0x24, 0x91, 0x58, 0x2D, 0x0C, 0x2D, 0x2B, 0x0D, 0xB1, 0xA0, 0xBD, 0x66, 0x8B, 0xD9, 0x54,
    0x93, 0xE5, 0xB3, 0x07, 0x60, 0x33, 0x9C, 0x9A, 0x3F, 0x8A, 0x6A, 0xF7, 0xBF, 0x90, 0x87, 0xD0,
    0xBF, 0x51, 0x1D, 0x4D, 0x67, 0xB4, 0xA4, 0x02, 0x41, 0x20, 0xF7, 0x15, 0xD3, 0xFC, 0x13, 0x85,
    0x33, 0x99, 0xE4, 0x7E, 0x46, 0xA4, 0x53, 0x79, 0x13, 0xB4, 0x8B, 0x20, 0x61, 0x2B, 0x58, 0x5E,
    0xC4, 0x1B, 0x0C, 0xFE, 0x56, 0xAC, 0xB4, 0x66, 0x99, 0xCB, 0x6C, 0xC9, 0x25, 0x99, 0xBF, 0x84,
    0x7F, 0xA6, 0x9A, 0x8E, 0x28, 0xA7, 0x84, 0x33, 0x92, 0xAF, 0xC1, 0x65, 0xC1, 0xA9, 0x8B, 0xC3,
    0xA4, 0x8E, 0xE6, 0xFB, 0xD0, 0xFE, 0xFA, 0xF0, 0x07, 0x39, 0xED, 0x5C, 0x6F, 0x03, 0xC7, 0x6D,
    0x95, 0x8C, 0xD3, 0x2C, 0xDE, 0x51, 0xF0, 0xED, 0x40, 0x0D, 0x61, 0xE5, 0xD9, 0x71, 0xD6, 0xF4,
    0x96, 0x98, 0xC6, 0x8C, 0xCA, 0xCC, 0x03, 0x58, 0x11, 0x71, 0xCE, 0x69, 0xAF, 0x12, 0xD0, 0x34,
    0x70, 0xAC, 0x82, 0x45, 0xF2, 0x83, 0x00, 0x83, 0x37, 0xBD, 0xB3, 0x7A, 0xCF, 0x96, 0x19, 0xBC,
    0x90, 0xEA, 0x85, 0x83, 0x12, 0xB7, 0x1F, 0x9D, 0x05, 0xC1, 0xC2, 0xEA, 0x98, 0x48, 0xF7, 0x57,
    0x04, 0x83, 0x82, 0xBC, 0x62, 0x86, 0xCF, 0xBB, 0x20, 0x5B, 0x61, 0xB7, 0xCF, 0xFB, 0x7A, 0xA4,
    0x09, 0xBE, 0x30, 0x17, 0x27, 0x95, 0xF9, 0xAB, 0x11, 0x6D, 0x50, 0x4E, 0x0D, 0x8F, 0xF3, 0xA6,
    0x40, 0x19, 0xD5, 0x6D, 0xFC, 0x11, 0x0A, 0xDB, 0xAE, 0x45, 0x8F, 0x7A, 0x56, 0xE2, 0x48, 0x46,
    0x0D, 0xD5, 0x4A, 0xDB, 0xED, 0x4F, 0x6B, 0xD5, 0x52, 0x28, 0x93, 0x22, 0xE0, 0x90, 0xDE, 0xE2,
    0x91, 0x5F, 0x4E, 0x9A, 0xE0, 0x60, 0x92, 0x0D, 0x04, 0x28, 0x39, 0x06, 0xED, 0x12, 0x81, 0xFC,
    0x22, 0x89, 0xE1, 0x91, 0x5C, 0x99, 0x18, 0x66, 0xE1, 0x17, 0xE4, 0xF3, 0xFA, 0x7F, 0x3A, 0x86,
    0x1B, 0xB4, 0xD8, 0xBD, 0xED, 0x4D, 0x00, 0x60, 0x86, 0x04, 0xB1, 0xDC, 0x14, 0x96, 0xCF, 0x52,
    0x2A, 0xF8, 0x63, 0x72, 0xBF, 0xC2, 0x73, 0x74, 0x8B, 0xCD, 0x31, 0x66, 0x2A, 0xA7, 0xEF, 0x42,
    0xB5, 0xC8, 0x03, 0x8E, 0xB5, 0xD1, 0x0E, 0x5B, 0x35, 0x36, 0xB0, 0x36, 0xB5, 0x77, 0x11, 0x24,
    0x1C, 0x1B, 0x76, 0xB0, 0xF9, 0x35, 0xB9, 0x02, 0xF9, 0x1A, 0x72, 0xA8, 0xB7, 0x23, 0x81, 0x58,
    0xFA, 0x65, 0xDF, 0x3C, 0x6B, 0xDD, 0xC7, 0xE9, 0x5A, 0x7A, 0xFD, 0x57, 0xE1, 0x63, 0x08, 0x8B,
    0xBA, 0x57, 0xFA, 0x54, 0x54, 0xE7, 0xF8, 0x3C, 0x4C, 0xF7, 0x9B, 0x50, 0x75, 0x5E, 0x5B, 0xC8,
    0xFE, 0x6D, 0xF0, 0x57, 0x81, 0x5A, 0x5A, 0x8D, 0x59, 0x8B, 0x46, 0x59, 0x85, 0xA5, 0x38, 0x03,
    0xBF, 0xBD, 0x25, 0xA1, 0x81, 0xE3, 0x9B, 0xD4, 0x77, 0x35, 0xF7, 0x16, 0xEE, 0x4F, 0xFA, 0x68,
    0x1A, 0xD9, 0x8C, 0xFA, 0x86, 0xB1, 0xBA, 0xAE, 0x05, 0x2C, 0x63, 0x7B, 0x0B, 0x62, 0xF9, 0x3D,
    0x6E, 0x7B, 0xD4, 0x13, 0x71, 0xDE, 0xFD, 0x2A, 0xC4, 0x58, 0x7F, 0x3A, 0x85, 0x07, 0x24, 0xFD,
    0xAA, 0xC2, 0x12, 0x09, 0x16, 0x17, 0xA7, 0xB4, 0x9A, 0xE6, 0x81, 0x6C, 0x72, 0x29, 0x01, 0xCD,
    0xEA, 0xBB, 0x8F, 0x35, 0x9A, 0x4F, 0x4C, 0x1C, 0x36, 0x64, 0x9B, 0x4F, 0xAC, 0xDA, 0x19, 0x8A,
    0xB0, 0x20, 0x90, 0x45, 0xD4, 0xFF, 0x00, 0x6A, 0x0E, 0xA9, 0x8E, 0x8F, 0xC1, 0x1D, 0x54, 0xA8,
    0x96, 0x49, 0x08, 0xC7, 0xE5, 0x49, 0xC1, 0xEA, 0x70, 0x4F, 0x4C, 0x9A, 0x37, 0x8A, 0xCB, 0x7F,
    0x22, 0x1D, 0xA4, 0x80, 0xBB, 0xBE, 0xE7, 0xFE, 0xAB, 0x8B, 0x3E, 0x18, 0xAD, 0xA2, 0xF8, 0xE6,
    0xDE, 0x99, 0x9D, 0x10, 0x60, 0x91, 0xA2, 0xE0, 0xDB, 0x9E, 0xD4, 0x76, 0x5B, 0xEB, 0x5A, 0x40,
    0x40, 0x52, 0x2D, 0x91, 0xD4, 0x5A, 0xBB, 0x4E, 0x00, 0x73, 0xB7, 0x36, 0x14, 0x3D, 0x1F, 0xED,
    0x18, 0x82, 0x6D, 0x77, 0xBE, 0x6A, 0x25, 0x03, 0x78, 0xAC, 0xCA, 0xF3, 0x47, 0x18, 0x6B, 0x90,
    0xBE, 0xA1, 0x6E, 0xB4, 0x9A, 0x31, 0x48, 0x98, 0x5F, 0x3D, 0x33, 0x43, 0x77, 0x3B, 0xAE, 0x49,
    0x2C, 0x08, 0xB9, 0xAE, 0x42, 0x47, 0x98, 0x79, 0x60, 0xB8, 0xFC, 0xE9, 0x50, 0xA3, 0x7A, 0x40,
    0x64, 0x31, 0xA3, 0x5C, 0xE6, 0xE7, 0xFA, 0xD1, 0x65, 0x7D, 0xEE, 0xE7, 0xBD, 0x53, 0xC3, 0x0F,
    0xEC, 0xA4, 0x7B, 0x70, 0x76, 0x83, 0xDF, 0xBD, 0x4A, 0x1B, 0x97, 0x63, 0xDE, 0xBB, 0x70, 0x2A,
    0x8D, 0x91, 0x9B, 0xB6, 0x5D, 0x56, 0xC9, 0x54, 0x36, 0xCD, 0x13, 0xF7, 0x7D, 0xE8, 0x44, 0xF2,
    0x2E, 0x6A, 0xF6, 0x20, 0xEF, 0x86, 0xAE, 0xED, 0x6A, 0xFB, 0x02, 0x6A, 0x75, 0x6E, 0xAF, 0xAB,
    0x69, 0xF7, 0x0D, 0xAA, 0x7C, 0xBF, 0x8C, 0xD5, 0x34, 0x12, 0x88, 0x1E, 0x69, 0x4F, 0xEE, 0xC6,
    0x48, 0xBD, 0x03, 0x69, 0x9C, 0xB9, 0x1C, 0x58, 0x11, 0xEF, 0xFE, 0xE6, 0xA3, 0x91, 0xEC, 0xA4,
    0x56, 0x86, 0xA1, 0x9C, 0xA6, 0x8E, 0x59, 0x41, 0xCB, 0x31, 0x54, 0xF6, 0xA4, 0x94, 0x58, 0x71,
    0x44, 0x99, 0xC3, 0x08, 0xD1, 0x05, 0x94, 0x0D, 0xD6, 0xF7, 0x39, 0xAA, 0x12, 0x00, 0x24, 0xF0,
    0x2A, 0x90, 0x55, 0x14, 0x2C, 0xBA, 0x55, 0xB2, 0x76, 0xFE, 0x75, 0x61, 0x6B, 0x1C, 0xD5, 0x15,
    0x80, 0x00, 0x9E, 0x4F, 0x35, 0x21, 0xC6, 0x45, 0xBF, 0x5A, 0x36, 0x0A, 0x2B, 0x33, 0x15, 0x8D,
    0x8D, 0xEA, 0xA8, 0x71, 0xD3, 0x18, 0xAA, 0xEA, 0x9B, 0xF6, 0x63, 0xFF, 0x00, 0xD0, 0xAE, 0x4B,
    0x05, 0x1D, 0x4D, 0x6B, 0xD8, 0x6B, 0x43, 0x11, 0x35, 0xAC, 0x3B, 0xF2, 0x7D, 0xA9, 0xAF, 0x12,
    0x8C, 0xC9, 0xA3, 0x82, 0x71, 0xCA, 0x1D, 0xA6, 0xDD, 0x88, 0xC5, 0x22, 0x08, 0x07, 0x2D, 0xF6,
    0xAD, 0x58, 0x13, 0xF1, 0x5E, 0x17, 0xA8, 0x88, 0x8B, 0xFA, 0x49, 0x5C, 0xF5, 0x19, 0xA4, 0xCC,
    0xAE, 0x21, 0x86, 0x99, 0x91, 0x11, 0xD9, 0x7B, 0xE0, 0xDA, 0xA3, 0x48, 0xDB, 0xCC, 0x8D, 0x73,
    0xDE, 0x85, 0xAA, 0x56, 0xF2, 0xAE, 0xBC, 0x81, 0xFA, 0x54, 0xE8, 0x96, 0xC8, 0x73, 0xC9, 0x22,
    0xB8, 0x4E, 0x80, 0x6F, 0xB5, 0xAF, 0xF1, 0x63, 0x5C, 0x16, 0xC5, 0xCF, 0xCD, 0x09, 0x5F, 0x14,
    0x54, 0x5F, 0x32, 0x54, 0x88, 0xDF, 0xD4, 0xD6, 0x36, 0xED, 0x48, 0x95, 0xBA, 0x10, 0x7B, 0x4E,
    0x9E, 0x4E, 0x8A, 0x25, 0x61, 0x62, 0x46, 0xE2, 0x3E, 0x7F, 0xC5, 0x44, 0x47, 0xD4, 0xF7, 0xE9,
    0x9A, 0xBE, 0xA5, 0xD9, 0x9E, 0xCA, 0x00, 0x51, 0xC5, 0x2E, 0xB7, 0x59, 0x58, 0x1F, 0xDE, 0x03,
    0xF9, 0xD7, 0xA5, 0xEA, 0x92, 0x22, 0xB7, 0xB0, 0xCC, 0xC7, 0x6D, 0xED, 0xCD, 0x40, 0xE9, 0x7A,
    0xB1, 0x19, 0x55, 0xE6, 0xC0, 0x0A, 0x83, 0xF5, 0x10, 0x28, 0x80, 0xEB, 0x17, 0x9A, 0x38, 0xAF,
    0x60, 0xE0, 0xDF, 0xEC, 0x31, 0xFA, 0xD3, 0x12, 0x4A, 0xB1, 0xA3, 0x6C, 0xC3, 0x2A, 0x85, 0x18,
    0xE6, 0xF8, 0x14, 0xAC, 0xAC, 0x11, 0xE3, 0x62, 0x2E, 0x6C, 0xC0, 0x5B, 0xE2, 0xB9, 0x99, 0xA5,
    0x98, 0x48, 0x16, 0xCA, 0x46, 0x07, 0xC6, 0x2A, 0x52, 0xF7, 0x48, 0x75, 0xEA, 0x5A, 0xF7, 0x27,
    0xBF, 0x15, 0x46, 0x61, 0xBF, 0x6F, 0x41, 0x9A, 0xB1, 0x3B, 0x54, 0x93, 0xC0, 0xA0, 0xA5, 0xF2,
    0x4D, 0xEE, 0xC6, 0xFC, 0xD5, 0x98, 0xA8, 0xB9, 0xB5, 0xB8, 0xA8, 0x06, 0xD7, 0xF8, 0xA9, 0x24,
    0xDB, 0x93, 0xF9, 0xD4, 0x64, 0x1E, 0xBC, 0x77, 0xA5, 0x08, 0x2D, 0x59, 0x36, 0x8C, 0x77, 0x6A,
    0x22, 0xDD, 0x80, 0x17, 0xB0, 0xF6, 0xA1, 0x4F, 0xEB, 0x92, 0x21, 0x73, 0x82, 0x4D, 0x19, 0x45,
    0x88, 0x37, 0xEB, 0x59, 0x75, 0x99, 0xF0, 0x90, 0xA0, 0x70, 0x3F, 0x3A, 0xDA, 0xF0, 0x76, 0x1B,
    0xC2, 0x93, 0x7B, 0xF2, 0x2B, 0x1B, 0xB5, 0x69, 0xF8, 0x53, 0x11, 0xA9, 0x1D, 0xBE, 0x28, 0xCD,
    0x7C, 0x45, 0x5D, 0x31, 0xE6, 0x53, 0x14, 0xCE, 0x82, 0xD7, 0x8D, 0x98, 0x58, 0xF5, 0x5A, 0xB4,
    0x1E, 0x92, 0x2E, 0x3D, 0x24, 0x8B, 0xE3, 0x8A, 0x9D, 0x71, 0xFF, 0x00, 0xCD, 0x99, 0xEF, 0xC4,
    0x8C, 0xB7, 0xEC, 0x6E, 0x6B, 0xA2, 0x56, 0x93, 0x4A, 0xD2, 0x5A, 0xC5, 0x0D, 0xAD, 0xF6, 0x35,
    0xE6, 0xDA, 0x3A, 0x50, 0x25, 0x9B, 0x4D, 0x1B, 0xEE, 0x81, 0x1C, 0xDC, 0xFD, 0x13, 0x00, 0x47,
    0xE9, 0x45, 0xD1, 0xCC, 0xDB, 0xA5, 0x79, 0x08, 0x58, 0xCF, 0x0A, 0x3F, 0x8B, 0xA5, 0xBE, 0xD7,
    0xA5, 0x23, 0x9C, 0x29, 0xB0, 0x00, 0xF4, 0xC0, 0x02, 0x9C, 0xD3, 0xBA, 0x49, 0x10, 0x2C, 0x09,
    0x70, 0x78, 0xED, 0x7A, 0xA6, 0x18, 0x5C, 0xD5, 0x89, 0x3E, 0x1D, 0x2C, 0xE0, 0x9B, 0xAA, 0x1B,
    0x77, 0x34, 0x28, 0x99, 0x8E, 0xA5, 0x4B, 0x1C, 0x11, 0x61, 0x45, 0x2A, 0x59, 0xB0, 0xD6, 0xF8,
    0x14, 0xA4, 0xF2, 0x34, 0x72, 0xAE, 0xDB, 0x90, 0xA6, 0xE4, 0x9A, 0xED, 0x9E, 0xB6, 0xC9, 0xC4,
    0xD3, 0x00, 0x19, 0x07, 0xE7, 0x42, 0x63, 0xEB, 0xA2, 0x21, 0x06, 0xE7, 0xDA, 0x85, 0xF5, 0x36,
    0x0D, 0xCD, 0xE8, 0x80, 0x90, 0x6D, 0xA8, 0x81, 0xC8, 0xB8, 0x56, 0xBF, 0xE8, 0x45, 0x59, 0xBD,
    0x24, 0xA8, 0x3E, 0x95, 0xC0, 0xA1, 0xCB, 0x21, 0x84, 0xA3, 0x80, 0x0D, 0x98, 0x5C, 0x77, 0xAB,
    0x48, 0xDB, 0x6E, 0xCD, 0xD3, 0x9A, 0x09, 0x2B, 0xB3, 0x7D, 0x02, 0x94, 0xEE, 0x60, 0x97, 0xF9,
    0xA9, 0x20, 0x00, 0x3F, 0xB5, 0x52, 0x30, 0x7E, 0xA2, 0x32, 0x68, 0x9C, 0x01, 0xF1, 0x5B, 0xFD,
    0x09, 0xC2, 0xC4, 0x72, 0x7F, 0x2A, 0xA9, 0x1F, 0x35, 0x23, 0x83, 0x91, 0x54, 0x66, 0xCD, 0x63,
    0x14, 0x06, 0xFA, 0x85, 0x19, 0xC2, 0x9B, 0xD3, 0x16, 0xE3, 0xD5, 0xD7, 0xB5, 0x24, 0x86, 0xDA,
    0x86, 0x39, 0xB0, 0x16, 0xA6, 0xEE, 0x1A, 0xC4, 0x11, 0x7A, 0xD1, 0x66, 0x65, 0xB3, 0x5A, 0xBE,
    0x14, 0x01, 0xB9, 0xEB, 0x70, 0x2B, 0x26, 0xEC, 0xA4, 0xEE, 0x15, 0xB5, 0xE1, 0x0A, 0x3D, 0x06,
    0xF8, 0x2F, 0x7F, 0xB0, 0x14, 0x67, 0xEA, 0x05, 0xD3, 0xCF, 0xEB, 0xD8, 0xAF, 0x89, 0x6A, 0x85,
    0x81, 0x06, 0x46, 0x16, 0x3F, 0x34, 0xC6, 0x92, 0x40, 0xBA, 0x4D, 0x83, 0x9B, 0xE4, 0x56, 0x7E,
    0xA2, 0x51, 0x34, 0xF3, 0x3F, 0xF1, 0x3B, 0x30, 0xFC, 0xE8, 0xD1, 0x48, 0xA2, 0x40, 0x6D, 0x65,
    0x39, 0xB5, 0xFD, 0xAB, 0xCB, 0x9A, 0xB2, 0xE5, 0x23, 0xD3, 0x4A, 0xC4, 0x13, 0x60, 0x07, 0x03,
    0xAD, 0x39, 0xA5, 0x85, 0xA1, 0x59, 0x0B, 0x81, 0x72, 0x07, 0x5F, 0x9A, 0x13, 0x4F, 0xBC, 0x6D,
    0x26, 0xCD, 0xFB, 0xA4, 0x51, 0x23, 0x9C, 0x34, 0x8C, 0x84, 0xDC, 0x11, 0x6E, 0x7B, 0x55, 0xF1,
    0x3A, 0x9A, 0x34, 0xD7, 0xC5, 0x9C, 0xC4, 0xA2, 0x16, 0xE5, 0x9B, 0x8A, 0x59, 0xE3, 0x22, 0x07,
    0x27, 0x92, 0x29, 0xA9, 0x48, 0x2C, 0xA4, 0xF0, 0x05, 0xAD, 0x54, 0x9C, 0x7E, 0xC5, 0x87, 0x52,
    0x2B, 0xBA, 0x4A, 0xD1, 0x04, 0xC2, 0x69, 0x9B, 0x76, 0x95, 0x1A, 0xFD, 0x05, 0x72, 0xF2, 0x28,
    0x5A, 0x4F, 0x4C, 0x26, 0x32, 0x72, 0xA4, 0xD1, 0x94, 0xE7, 0xBE, 0x29, 0x57, 0x0C, 0xCE, 0xF4,
    0xB3, 0x58, 0xDB, 0xD2, 0x41, 0xCD, 0x02, 0x5F, 0x5E, 0x07, 0x00, 0xD4, 0x6F, 0xB6, 0xE3, 0xD5,
    0x8E, 0xD1, 0x57, 0xB6, 0x31, 0x6E, 0x2B, 0x5D, 0x87, 0x85, 0x87, 0xCF, 0xE9, 0x50, 0x4E, 0x06,
    0x6B, 0x88, 0x00, 0xF2, 0x2A, 0x1A, 0xD6, 0xE7, 0xBD, 0x10, 0x10, 0x4D, 0x81, 0xC9, 0xA5, 0xC9,
    0x2E, 0xE1, 0x17, 0xAF, 0x5A, 0x23, 0x7A, 0x9B, 0x62, 0x7D, 0x47, 0xF4, 0xAB, 0xA4, 0x21, 0x66,
    0x8C, 0x03, 0x70, 0x01, 0x27, 0xDC, 0xD2, 0xD5, 0x8D, 0xC2, 0x24, 0xD3, 0x91, 0xB5, 0xA2, 0xE5,
    0x70, 0x47, 0x71, 0x57, 0x54, 0x56, 0x53, 0x70, 0x43, 0x7B, 0x62, 0x88, 0xD8, 0xC1, 0xFB, 0xD0,
    0xC8, 0x75, 0x37, 0x04, 0xB0, 0x1D, 0x0D, 0x3D, 0x24, 0x29, 0x2A, 0xFB, 0x49, 0x0A, 0x4B, 0x0E,
    0xC6, 0xB5, 0x22, 0x9F, 0xCA, 0xF0, 0xAD, 0x4C, 0x9F, 0x49, 0x48, 0x8A, 0x8F, 0x96, 0x36, 0xAC,
    0xA0, 0x01, 0x3B, 0x94, 0xF3, 0xC8, 0xA2, 0xEB, 0x25, 0xB6, 0x81, 0x20, 0x04, 0x6E, 0x91, 0xF7,
    0x91, 0x7E, 0x83, 0x03, 0xF5, 0x27, 0xF2, 0xA9, 0x65, 0x75, 0x06, 0x18, 0xF4, 0xC9, 0xB5, 0x88,
    0xED, 0x56, 0x1C, 0x7C, 0x0A, 0x20, 0x4B, 0x8C, 0xDB, 0xF3, 0xAA, 0x6D, 0x37, 0x38, 0xE2, 0xB8,
    0x2C, 0xB1, 0x0C, 0x78, 0x1F, 0xC2, 0x30, 0x7E, 0xF4, 0x43, 0x27, 0xE1, 0xCA, 0xEF, 0x53, 0xBC,
    0x75, 0xE9, 0x6A, 0x16, 0x15, 0xFE, 0xAC, 0x81, 0x52, 0xE0, 0x88, 0x60, 0x32, 0x36, 0xF5, 0x37,
    0x3B, 0x4F, 0x41, 0x4E, 0x82, 0x69, 0x30, 0x0D, 0x29, 0x3C, 0x8E, 0x95, 0x2C, 0x01, 0x27, 0xFF,
    0x00, 0xAF, 0xF3, 0xAA, 0x44, 0xEA, 0xD1, 0xAB, 0x2E, 0x40, 0x1F, 0xCA, 0xAC, 0xB7, 0x1C, 0x9C,
    0xF3, 0x7F, 0x7A, 0xF4, 0xA2, 0xED, 0x59, 0xCC, 0xF4, 0x09, 0xBF, 0x64, 0xE5, 0xBA, 0x1C, 0x35,
    0x15, 0x58, 0x58, 0xD8, 0xF4, 0xAE, 0x2A, 0x1C, 0x10, 0x69, 0x78, 0xD2, 0x44, 0x9F, 0xCA, 0x50,
    0x5B, 0x77, 0x00, 0x73, 0x4B, 0x2D, 0x6C, 0x2B, 0x67, 0x59, 0xEE, 0x08, 0x17, 0xB7, 0xF7, 0xAB,
    0xA9, 0xE6, 0xA0, 0x7A, 0x09, 0x04, 0x11, 0x9E, 0x0D, 0x55, 0x44, 0x8E, 0x4E, 0xDE, 0x07, 0x53,
    0x53, 0x8F, 0x46, 0x61, 0x0B, 0x71, 0x9A, 0x1B, 0xB3, 0x30, 0xB2, 0x82, 0x4D, 0xE8, 0xC9, 0x00,
    0xC6, 0xEF, 0x51, 0xF8, 0xAA, 0xAB, 0xEE, 0xD4, 0x94, 0x02, 0xC1, 0x06, 0x3E, 0x6A, 0x95, 0xFA,
    0x2D, 0x93, 0x1C, 0x7E, 0x5A, 0x10, 0x48, 0xDC, 0x79, 0x3D, 0xAA, 0xEA, 0x2D, 0x93, 0xD2, 0xAB,
    0xBB, 0xD6, 0x41, 0xF8, 0xAB, 0x9C, 0x00, 0x2E, 0x09, 0xA2, 0x62, 0xBB, 0xF1, 0x63, 0x9F, 0x7A,
    0xA3, 0x35, 0x85, 0xAA, 0x38, 0x26, 0xA6, 0x34, 0xDE, 0xD9, 0xC0, 0xEA, 0x69, 0x6C, 0x25, 0x77,
    0x6C, 0x5D, 0xC7, 0xF2, 0xEF, 0x4B, 0xB9, 0x32, 0xB5, 0xD8, 0xFA, 0x8D, 0x39, 0xAF, 0x84, 0xC4,
    0x21, 0x79, 0x01, 0x54, 0x71, 0xE9, 0xC7, 0x36, 0xFF, 0x00, 0xBA, 0x4D, 0xA2, 0x79, 0x3F, 0xE2,
    0x65, 0x6F, 0x6B, 0xDA, 0xB8, 0xB2, 0xC9, 0xB9, 0x51, 0x48, 0xF0, 0xA6, 0x6E, 0x06, 0x16, 0xE6,
    0x88, 0x08, 0x0C, 0x41, 0xFD, 0xD5, 0x18, 0x35, 0x36, 0x90, 0xA8, 0x59, 0x50, 0xAB, 0x8E, 0x1A,
    0xC3, 0x35, 0x77, 0x76, 0xB0, 0x23, 0x04, 0x8B, 0x1C, 0x0A, 0x90, 0x41, 0xBC, 0x0A, 0xAD, 0x7B,
    0x11, 0x71, 0x83, 0xC8, 0x34, 0x25, 0x88, 0xCA, 0x54, 0x23, 0x6E, 0xB6, 0x15, 0x40, 0xF7, 0xA6,
    0xA0, 0x61, 0x21, 0x2B, 0x18, 0x03, 0x37, 0x20, 0x9B, 0xDF, 0xED, 0x50, 0x0A, 0xA2, 0x87, 0x04,
    0xAB, 0x92, 0x7A, 0xF1, 0xF1, 0x46, 0xC6, 0x2F, 0xA4, 0x56, 0x84, 0x48, 0x8F, 0x60, 0x79, 0x02,
    0xAF, 0x7B, 0x1B, 0xD4, 0xE8, 0xA2, 0xDD, 0x30, 0x2C, 0x38, 0x5B, 0xDB, 0xF4, 0xAE, 0x98, 0x08,
    0xCB, 0x5C, 0xD8, 0x0A, 0xEC, 0xC3, 0x27, 0xE1, 0xB2, 0x32, 0xE9, 0x6F, 0x53, 0x0F, 0xD9, 0x8B,
    0xBF, 0x4A, 0x0C, 0x5E, 0x1D, 0xE2, 0x51, 0xCE, 0x27, 0x8D, 0x77, 0x38, 0x37, 0xDC, 0x18, 0x7F,
    0x5A, 0xD7, 0xD0, 0xC4, 0x89, 0x18, 0x27, 0x2C, 0x72, 0x69, 0xE6, 0xDC, 0xB1, 0x92, 0x96, 0xB8,
    0x15, 0x29, 0xE5, 0x73, 0x65, 0xE3, 0x8B, 0xC5, 0x09, 0xA3, 0x4A, 0xF1, 0xB7, 0xE3, 0x34, 0xC8,
    0xA0, 0x0C, 0x9D, 0xC0, 0x8F, 0xCA, 0x92, 0x95, 0x63, 0x8F, 0xD5, 0x0A, 0x59, 0x5F, 0x35, 0xA0,
    0x50, 0x49, 0x18, 0x32, 0x31, 0x7B, 0x8B, 0x91, 0xC0, 0xA5, 0x75, 0x60, 0x32, 0x58, 0x60, 0x8E,
    0x28, 0x63, 0x95, 0x48, 0x6C, 0x90, 0xB8, 0x89, 0xEF, 0x20, 0x82, 0xC6, 0xA8, 0x10, 0xAC, 0xE5,
    0xBA, 0x11, 0x9A, 0x83, 0x61, 0x92, 0x73, 0x51, 0xB8, 0x9E, 0xA6, 0xDD, 0xBB, 0xD7, 0x63, 0x91,
    0xC9, 0x44, 0x9B, 0x6E, 0x3D, 0xEA, 0x09, 0xB9, 0xE6, 0xB9, 0x80, 0x23, 0x75, 0x50, 0x92, 0x78,
    0x23, 0xDE, 0x91, 0xB1, 0x92, 0x2F, 0xC9, 0xF6, 0xE9, 0x47, 0xD2, 0x80, 0x65, 0x4D, 0xD6, 0xDB,
    0x7C, 0xD2, 0xC0, 0x10, 0x7E, 0xA3, 0xF9, 0x51, 0xA3, 0x40, 0xE4, 0x28, 0x17, 0x27, 0x02, 0xF4,
    0xD1, 0x03, 0x34, 0x7F, 0xF5, 0x1B, 0x45, 0x27, 0x87, 0xC3, 0x66, 0xB9, 0x59, 0x6C, 0xBB, 0x4E,
    0x38, 0xCF, 0xF4, 0xAF, 0x38, 0x50, 0xF3, 0xB8, 0x2F, 0xBD, 0x6A, 0x78, 0xB0, 0x58, 0x34, 0xF1,
    0xE9, 0xD9, 0xAE, 0x8B, 0x20, 0x60, 0x47, 0x40, 0x46, 0x6B, 0x2C, 0x84, 0x57, 0x2A, 0xA7, 0xCC,
    0x40, 0x70, 0xC0, 0x5A, 0xF5, 0xC5, 0x91, 0x54, 0x8A, 0x47, 0x81, 0x15, 0xD8, 0x2F, 0xFC, 0xA5,
    0xC0, 0xFB, 0xDA, 0xAE, 0xB3, 0xEE, 0x2A, 0x1E, 0xD6, 0x3D, 0xE9, 0x74, 0x4B, 0x37, 0xEC, 0x9E,
    0xFD, 0xC7, 0x5F, 0xF3, 0x56, 0x53, 0x1C, 0xC0, 0x03, 0x82, 0x2A, 0x74, 0x86, 0x3F, 0xFF, 0xD9};

// Mock functions for testing (replace with actual hardware functions)
int initialize_board(void)
{
    // Simulate board initialization (return 0 for success)
    return 0;
}

int check_board_response(void)
{
    // Simulate board response (return 1 for success)
    return 1;
}

// Test cases
void test_board_initialization(void)
{
    TEST_ASSERT_EQUAL_INT(0, initialize_board());
}

void test_board_response(void)
{
    TEST_ASSERT_EQUAL_INT(1, check_board_response());
}

data d;
void setUp(void)
{
    // This function is called before each test
    // initializeDebug();
    int powerStartPoint = 50;
    int sensorStartPoint = 0;
    // populate power vector with random values
    for (size_t i = 0; i < NUM_DATA_POINTS; i++)
    {

        d.power.push_back(powerStartPoint + i); // random power values between 0 and 100
    }
    // populate height with a random value

    for (size_t i = 0; i < NUM_DATA_POINTS; i++)
    {
        d.temp.push_back(random(0, 100)); // random lift flag values (0 or 1)
    }
    // d.img = image_data;
    initPot();
}
void tearDown(void)
{
    // This function is called after each test
    // Clean up any resources if needed
    // For example, if you allocated memory, free it here
    if (d.img != nullptr)
    {
        free(d.img);
        d.img = nullptr;
    }
}

void test_checkPower()
{
    // I don't know how this function is going to work.
}

void test_getHeight()
{
    Serial.println("This test will be interactive to verify the height at different real world positions:\n");
    Serial.println("Setting the max height:");
    setMaxHeight();
    Serial.println("Pot Value: " + String(getRawPotValue()));
    Serial.println("Height Value in Feet before setZeroHeight: " + String(getHeight()));
    Serial.println("-----------------------------");
    Serial.println("Move the cord to its limit and set the Min Height:");
    delay(10000);
    Serial.println("Pot Value: " + String(getRawPotValue()));
    Serial.println("Height Value in Feet before setZeroHeight: " + String(getHeight()));
    setZeroHeight();

    float currHeight = getHeight();
    TEST_ASSERT_TRUE(currHeight == 0);

    Serial.println("Height Value in feet after calibration: " + String(currHeight));
    Serial.println("Now move 1 foot up and Record the height again.");
    delay(10000);

    currHeight = getHeight();
    Serial.println("Height Value in Feet after moving up: " + String(currHeight));
    bool oneFootUp = (currHeight > 0.8 && currHeight < 1.2);
    TEST_ASSERT_TRUE(oneFootUp); // Allow a tolerance of 0.1 feet

    Serial.println("Height Value in Feet after moving up: " + String(currHeight));
}

void heightInstantiation()
{
    setMaxHeight();
    Serial.println("The max height is set.");
    Serial.println("pull ripcord out and wait:");
    delay(10000);
    setZeroHeight();
}

void pinInstantition()
{
    pinMode(LIFT_PIN, OUTPUT);
    digitalWrite(LIFT_PIN, LOW);
    pinMode(LOWER_PIN, OUTPUT);
    digitalWrite(LOWER_PIN, LOW);
}

void test_liftWinch()
{
    heightInstantiation();
    pinInstantition();
    // lift the winch from zero to 3.5 feet

    TEST_ASSERT_TRUE(liftWinch(LIFT_PIN, 0, 3.5));
}

void test_liftWinch_stuck()
{
    heightInstantiation();

    TEST_ASSERT_FALSE(liftWinch(LIFT_PIN, 0, 3.5));
}
void test_getImage()
{
    initCamera();
    getImg(d);
    TEST_ASSERT_NOT_NULL(d.img);
}
void test_jsonify()
{
    JsonDocument dataJson = jsonify(d);

    // Check if the JSON document is not empty
    TEST_ASSERT_FALSE(dataJson.isNull());
    // serial print the JSON document to check if it is correctly formatted

    Serial.println("JSON Document:");
    Serial.println(serializeJson(d.doc, Serial));
}

// EVERYTHING BELOW WILL BE BLOCKED BY LORA MESSAGES

void test_sendData()
{
    TEST_ASSERT_TRUE(setupLoRa()); // Ensure LoRa is set up before sending data
    Serial.println("jsonify next");
    JsonDocument doc = jsonify(d);
    size_t len = measureJson(doc);
    char *buffer = new char[len + 1]; // +1 for null terminator
    Serial.print("Sending JSON: ");

    serializeJson(doc, buffer, len + 1);
    Serial.print("makes it past serializeJson: ");

    // Send the JSON over LoRa
    TEST_ASSERT_TRUE(sendData(d));
    delete[] buffer; // Free the allocated memory
}

void test_sendImage()
{

    TEST_ASSERT_NOT_NULL(d.img); // Ensure the image is captured
    TEST_ASSERT_TRUE(sendImage(d));
    // Check if the image was sent successfully
    // This might require mocking the sendCapturedImage function to verify the call
    TEST_ASSERT_TRUE(getCapturedImageSize() > 0); // Ensure image size is greater than 0
}

void test_FSM_initialization()
{
    initializeStartup(d);
    TEST_ASSERT_EQUAL(d.state, NORMAL);
    // Add more assertions to check other initializations if needed
}

void runTests()
{
    UNITY_BEGIN();

    // Test tests
    RUN_TEST(test_board_initialization);
    RUN_TEST(test_board_response);

    // RUN_TEST(test_checkPower);
    // RUN_TEST(test_getImage);
    // RUN_TEST(test_jsonify);
    // RUN_TEST(test_getHeight);
    RUN_TEST(test_liftWinch);

// LoRa Dependent  Tests
#if LORA_TESTS
    RUN_TEST(test_sendData);

#endif

#if SYSTEM_TESTS
    test_FSM_initialization();
#endif
    UNITY_END();
}

void setup()
{
    // wait 2 seconds for the unity test runner
    // establishes a serial connection with the board
    delay(2000);
    runTests();
}

void loop()
{
}
