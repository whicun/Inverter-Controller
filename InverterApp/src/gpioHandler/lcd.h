using byte = uint8_t;

byte empty[8] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
byte fullBox[8] = {
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F
};
byte halfBoxBottom[8] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x1F,
    0x1F,
    0x1F,
    0x1F
};
byte halfBoxTop[8] = {
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x00,
    0x00,
    0x00,
    0x00
};
byte topLeftAChar[8] = {
    0x01,
    0x03,
    0x07,
    0x0F,
    0x0F,
    0x1F,
    0x1F,
    0x1F      
};
byte sideLeftAChar[8] = {
    0x01,
    0x3,
    0x7,
    0xF,
    0x1F,
    0x1F,
    0x1F,
    0x1F
};
byte sideLeftAInnerChar[8] = {
    0x1F,
    0x1F,
    0x1E,
    0x1E,
    0x1C,
    0x18,
    0x10,
    0x10
};
byte sideLeftInnerCharConnector[8] = {
    0x1F,
    0x1F,
    0x1E,
    0x1C,
    0x1F,
    0x1F,
    0x1F,
    0x1F
};
byte topRightSCurve[8] = {
    0x10,
    0x18,
    0x1C,
    0x1E,
    0x1F,
    0x1F,
    0x1F,
    0x1F
};
byte topLeftSCurve[8] = {
    0x01,
    0x03,
    0x07,
    0x0F,
    0x1F,
    0x1F,
    0x1F,
    0x1F
};
byte bottomLeftSCurve[8] = {
    0x00,
    0x00,
    0x1C,
    0x1E,
    0x1E,
    0x0F,
    0x0F,
    0x07,
};
     