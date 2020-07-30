const char mySet[256] = {
    32,  // 0x00
    127,  // 0x01 Failure
    'T',  // 0x02
    'E',  // 0x03
    'M',  // 0x04
    'N',  // 0x05
    'A',  // 0x06
    'I',  // 0x07
    'O',  // 0x08
    'G',  // 0x09
    'K',  // 0x0A
    'D',  // 0x0B
    'W',  // 0x0C
    'R',  // 0x0D
    'U',  // 0x0E
    'S',  // 0x0F
    127,  // 0x10  Failure
    129,  // 0x11  Ø
    'Q',  // 0x12
    'Z',  // 0x13
    'Y',  // 0x14
    'C',  // 0x15
    'X',  // 0x16
    'B',  // 0x17
    'J',  // 0x18
    'P',  // 0x19
    130,  // 0x1A  Æ
    'L',  // 0x1B
    127,  // 0x1C  Failure
    'F',  // 0x1D
    'V',  // 0x1E
    'H',  // 0x1F
    '0',  // 0x20
    '9',  // 0x21
    127,  // 0x22  Failure
    '8',  // 0x23
    127,  // 0x24  Failure
    127,  // 0x25  Failure
    127,  // 0x26  Failure
    '7',  // 0x27
    127,  // 0x28  Failure
    133,  // 0x29
    137,  // 0x2a  Failure
    127,  // 0x2b  Failure
    127,  // 0x2c  Failure
    '/',  // 0x2d
    136,  // 0x2E   Failure
    '6',  // 0x2F
    '1',  // 0x30
    127,  // 0x31  Failure
    128,  // 0x32  Å
    127,  // 0x33  Failure
    127,  // 0x34  Failure
    134,  // 0x35  Failure
    127,  // 0x36  Failure
    135,  // 0x37  Failure
    '2',  // 0x38
    127,  // 0x39  Failure
    127,  // 0x3a  Failure
    127,  // 0x3b  Failure
    '3',  // 0x3C
    132,  // 0x3D  SN
    '4',  // 0x3E
    '5',  // 0x3F
    127,  // 0x40
    127,  // 0x41
    127,  // 0x42
    127,  // 0x43
    127,  // 0x44
    127,  // 0x45
    127,  // 0x46
    ':',  // 0x47
    127,  // 0x48
    127,  // 0x49
    127,  // 0x4A
    127,  // 0x4b
    ',',  // 0x4c
    127,  // 0x4d
    127,  // 0x4e
    127,  // 0x4f
    127,  // 0x50
    127,  // 0x51
    ')',  // 0x52
    127,  // 0x53
    '!',  // 0x54
    ';',  // 0x55
    127,  // 0x56
    127,  // 0x57
    127,  // 0x58
    127,  // 0x59
    127,  // 0x5a
    127,  // 0x5b
    127,  // 0x5c
    127,  // 0x5d
    173,  // 0x5E  Failure
    127,  // 0x5f
    127,  // 0x60
    39,  // 0x61  '
    127,  // 0x62
    127,  // 0x63
    127,  // 0x64
    127,  // 0x65
    127,  // 0x66
    127,  // 0x67
    127,  // 0x68
    127,  // 0x69
    '.',  // 0x6A
    127,  // 0x6b
    127,  // 0x6c
    '"',  // 0x6D
    127,  // 0x6e
    127,  // 0x6f
    127,  // 0x70
    127,  // 0x71
    95,  // 0x72  Failure
    '?',  // 0x73
    127,  // 0x74
    127,  // 0x75
    127,  // 0x76
    127,  // 0x77
    127,  // 0x78
    127,  // 0x79
    131,  // 0x7a  SK
    127,  // 0x7b
    127,  // 0x7c
    127,  // 0x7d
    127,  // 0x7e
    127,  // 0x7f
	127,  // 0x80
	127,  // 0x81
	127,  // 0x82
	127,  // 0x83
	127,  // 0x84
	127,  // 0x85
	127,  // 0x86
	127,  // 0x87
	127,  // 0x88
	127,  // 0x89
	127,  // 0x8A
	127,  // 0x8B
	127,  // 0x8C
	127,  // 0x8D
	127,  // 0x8E
	127,  // 0x8F
	127,  // 0x90
	127,  // 0x91
	127,  // 0x92
	127,  // 0x93
	127,  // 0x94
	127,  // 0x95
	127,  // 0x96
	127,  // 0x97
	127,  // 0x98
	127,  // 0x99
	127,  // 0x9A
	127,  // 0x9B
	127,  // 0x9C
	127,  // 0x9D
	127,  // 0x9E
	127,  // 0x9F
	127,  // 0xA0
	127,  // 0xA1
	127,  // 0xA2
	127,  // 0xA3
	127,  // 0xA4
	127,  // 0xA5
	127,  // 0xA6
	127,  // 0xA7
	127,  // 0xA8
	127,  // 0xA9
	127,  // 0xAA
	127,  // 0xAB
	127,  // 0xAC
	127,  // 0xAD
	127,  // 0xAE
	127,  // 0xAF
	127,  // 0xB0
	127,  // 0xB1
	127,  // 0xB2
	127,  // 0xB3
	127,  // 0xB4
	127,  // 0xB5
	127,  // 0xB6
	127,  // 0xB7
	127,  // 0xB8
	127,  // 0xB9
	138,  // 0xBA
	127,  // 0xBB
	127,  // 0xBC
	127,  // 0xBD
	127,  // 0xBE
	127,  // 0xBF
	127,  // 0xC0
	127,  // 0xC1
	127,  // 0xC2
	127,  // 0xC3
	127,  // 0xC4
	127,  // 0xC5
	127,  // 0xC6
	127,  // 0xC7
	127,  // 0xC8
	127,  // 0xC9
	127,  // 0xCA
	127,  // 0xCB
	127,  // 0xCC
	127,  // 0xCD
	127,  // 0xCE
	127,  // 0xCF
	127,  // 0xD0
	127,  // 0xD1
	127,  // 0xD2
	127,  // 0xD3
	127,  // 0xD4
	127,  // 0xD5
	127,  // 0xD6
	127,  // 0xD7
	127,  // 0xD8
	127,  // 0xD9
	127,  // 0xDA
	127,  // 0xDB
	127,  // 0xDC
	127,  // 0xDD
	127,  // 0xDE
	127,  // 0xDF
	127,  // 0xE0
	127,  // 0xE1
	127,  // 0xE2
	127,  // 0xE3
	127,  // 0xE4
	127,  // 0xE5
	127,  // 0xE6
	127,  // 0xE7
	127,  // 0xE8
	127,  // 0xE9
	127,  // 0xEA
	127,  // 0xEB
	127,  // 0xEC
	127,  // 0xED
	127,  // 0xEE
	127,  // 0xEF
	127,  // 0xF0
	127,  // 0xF1
	127,  // 0xF2
	127,  // 0xF3
	127,  // 0xF4
	127,  // 0xF5
	127,  // 0xF6
	127,  // 0xF7
	127,  // 0xF8
	127,  // 0xF9
	127,  // 0xFA
	127,  // 0xFB
	127,  // 0xFC
	127,  // 0xFD
	127,  // 0xFE
	127  // 0xFF
};