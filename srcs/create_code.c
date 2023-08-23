#include "../include/woody.h"


// unsigned char code[] = {    0x48, 0x31, 0xed,
//                             0x48, 0x83, 0xec, 0x20,
//                             0xc6, 0x04, 0x24, 0x60,
//                             0xc6, 0x44, 0x24, 0x01, 0x61,
//                             0xc6, 0x44, 0x24, 0x02, 0x62,
//                             0xc6, 0x44, 0x24, 0x03, 0x63,
//                             0xc6, 0x44, 0x24, 0x04, 0x64,
//                             0xc6, 0x44, 0x24, 0x05, 0x65,
//                             0xc6, 0x44, 0x24, 0x06, 0x66,
//                             0xc6, 0x44, 0x24, 0x07, 0x67,
//                             0xc6, 0x44, 0x24, 0x08, 0x68,
//                             0xc6, 0x44, 0x24, 0x09, 0x69,
//                             0xc6, 0x44, 0x24, 0x0a, 0x6a,
//                             0xc6, 0x44, 0x24, 0x0b, 0x6b,
//                             0xc6, 0x44, 0x24, 0x0c, 0x6c,
//                             0xc6, 0x44, 0x24, 0x0d, 0x6d,
//                             0xc6, 0x44, 0x24, 0x0e, 0x6e,
//                             0xc6, 0x44, 0x24, 0x0f, 0x6f,
//                             0xc6, 0x44, 0x24, 0x10, 0x70,
//                             0x66, 0xc7, 0x44, 0x24, 0x1d, 0x0f, 0x00,
//                             0x4c, 0x8b, 0x44, 0x24, 0x1d,
//                             0x49, 0x81, 0xe0, 0xff, 0x00, 0x00, 0x00,
//                             0xb8, 0x00, 0x00, 0x00, 0x00,
//                             0xbf, 0x01, 0x00, 0x00, 0x00,
//                             0x48, 0x8d, 0x34, 0x25, 0x20, 0x30, 0x40,
//                             0x00,
//                             0x4a, 0x8b, 0x14, 0x04,
//                             0xe8, 0x67, 0xff, 0xff, 0xff,
//                             0x66, 0x83, 0x6c, 0x24, 0x1d, 0x01,
//                             0x66, 0x83, 0x7c, 0x24, 0x1d, 0x00,
//                             0x7f, 0xcb,
//                             0xe9, 0x10, 0x50, 0x00, 0x00
//                         };
unsigned char code[] = {    0x48, 0x31, 0xED,
                            0x48, 0x83, 0xEC, 0x20,
                            0xC6, 0x04, 0x24, 0x60,
                            0xC6, 0x44, 0x24, 0x01, 0x61,
                            0xC6, 0x44, 0x24, 0x02, 0x62,
                            0xC6, 0x44, 0x24, 0x02, 0x63,
                            0xC6, 0x44, 0x24, 0x02, 0x64,
                            0xC6, 0x44, 0x24, 0x02, 0x65,
                            0xC6, 0x44, 0x24, 0x02, 0x66,
                            0xC6, 0x44, 0x24, 0x02, 0x67,
                            0xC6, 0x44, 0x24, 0x02, 0x68,
                            0xC6, 0x44, 0x24, 0x02, 0x69,
                            0xC6, 0x44, 0x24, 0x02, 0x6a,
                            0xC6, 0x44, 0x24, 0x02, 0x6b,
                            0xC6, 0x44, 0x24, 0x02, 0x6c,
                            0xC6, 0x44, 0x24, 0x02, 0x6d,
                            0xC6, 0x44, 0x24, 0x02, 0x6e,
                            0xC6, 0x44, 0x24, 0x02, 0x6f,
                            0x66, 0xC7, 0x44, 0x24, 0x1D, 0x0F, 0x00,
                            0x4C, 0x8B, 0x04, 0x24,
                            0x41, 0x24, 0xFF,
                            0x48, 0xC7, 0xC0, 0x00, 0x00, 0x00, 0x00,
                            0x48, 0xBF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x48, 0x8D, 0x35, 0x07, 0x00, 0x00, 0x00,
                            0x48, 0x8B, 0x34, 0x00,
                            0xE8, 0xB4, 0xFF, 0xFF, 0xFF,
                            0x66, 0x83, 0x6C, 0x24, 0x1D, 0x01,
                            0x66, 0x83, 0x7C, 0x24, 0x1D, 0x00,
                            0x7F, 0xCE,
                            0xE9, 0xFF, 0xFF, 0xFF, 0xFF
                        };