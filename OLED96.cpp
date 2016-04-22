/**************************
 * TEXT / STRING COMMANDS *
 **************************/

uint8_t moveCursor(uint16_t row, uint16_t col) {
	Serial.write(0xFF);
	Serial.write(0xE4);
	Serial.write(row >> 8);
	Serial.write(row & 0xFF);
	Serial.write(col >> 8);
	Serial.write(col & 0xFF);

	return (getResponse() == 6);
}

uint8_t putChar(uint16_t c) {
	Serial.write(0xFF);
	Serial.write(0xFE);
	Serial.write(c >> 8);
	Serial.write(c & 0xFF);

	return (getResponse() == 6);
}

uint8_t putStr(char *str) {
	Serial.write(0x00);
	Serial.write(0x06);
	uint8_t index = 0;
	uint8_t maximum = 0xFF;
	while ((uint8_t) str[index] && index < maximum) {
		Serial.write(0);
		Serial.write((uint8_t) str[index]);
		++index;
	}
	Serial.write(0);

	return (getResponse() == 6);
}

uint16_t getCharW(char c) {
	uint8_t ACK;
	uint16_t width;

	Serial.write(0x00);
	Serial.write(0x02);
	Serial.write(c);

	while (!Serial.available()) delay(1);
	ACK = Serial.read();
	width = Serial.read();
	width += Serial.read();

	if (!ACK) return 0;
	return width;
}

uint16_t getCharH(char c) {
	uint8_t ACK;
	uint16_t height;

	Serial.write(0x00);
	Serial.write(0x01);
	Serial.write(c);

	while (!Serial.available()) delay(1);
	ACK = Serial.read();
	height = Serial.read();
	height += Serial.read();

	if (!ACK) return 0;
	return height;
}

uint8_t setTextFG(uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0x7F);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint8_t setTextBG(uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0x7E);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint8_t setFont(uint8_t id) {
	if (id != 0 && id != 7) return 0;
	Serial.write(0xFF);
	Serial.write(0x7D);
	Serial.write(0);
	Serial.write(id);

	return (getResponse() == 6);
}

uint8_t setTextWM(uint8_t m) {
	if (m < 1 || m > 16) return 0;
	Serial.write(0xFF);
	Serial.write(0x7C);
	Serial.write(0);
	Serial.write(m);

	return (getResponse() == 6);
}

uint8_t setTextHM(uint8_t m) {
	if (m < 1 || m > 16) return 0;
	Serial.write(0xFF);
	Serial.write(0x7B);
	Serial.write(0);
	Serial.write(m);

	return (getResponse() == 6);
}

uint8_t setTextXGap(uint8_t g) {
	if (g > 32) return 0;
	Serial.write(0xFF);
	Serial.write(0x7A);
	Serial.write(0);
	Serial.write(g);

	return (getResponse() == 6);
}

uint8_t setTextYGap(uint8_t g) {
	if (g > 32) return 0;
	Serial.write(0xFF);
	Serial.write(0x79);
	Serial.write(0);
	Serial.write(g);

	return (getResponse() == 6);
}

uint8_t setBold(uint8_t m) {
	if (m > 1) return 0;
	Serial.write(0xFF);
	Serial.write(0x76);
	Serial.write(0);
	Serial.write(m);

	return (getResponse() == 6);
}

uint8_t setInverse(uint8_t m) {
	if (m > 1) return 0;
	Serial.write(0xFF);
	Serial.write(0x74);
	Serial.write(0);
	Serial.write(m);

	return (getResponse() == 6);
}

uint8_t setItalic(uint8_t m) {
	if (m > 1) return 0;
	Serial.write(0xFF);
	Serial.write(0x75);
	Serial.write(0);
	Serial.write(m);

	return (getResponse() == 6);
}

uint8_t setOpacity(uint8_t m) {
	if (m > 1) return 0;
	Serial.write(0xFF);
	Serial.write(0x77);
	Serial.write(0);
	Serial.write(m);

	return (getResponse() == 6);
}

uint8_t setUnderline(uint8_t m) {
	if (m > 1) return 0;
	Serial.write(0xFF);
	Serial.write(0x73);
	Serial.write(0);
	Serial.write(m);

	return (getResponse() == 6);
}

uint8_t setTextAttrib(uint8_t v) {
	Serial.write(0xFF);
	Serial.write(0x72);
	Serial.write(0);
	Serial.write(v & 0xF0);

	return (getResponse() == 6);
}

/**********************
 * GRAPHICS FUNCTIONS *
 **********************/

uint8_t clearScreen() {
	Serial.write(0xFF);
	Serial.write(0xD7);

	return (getResponse() == 6);
}

uint8_t chColor(uint16_t oldCol, uint16_t newCol) {
	Serial.write(0xFF);
	Serial.write(0xBE);
	Serial.write(oldCol >> 8);
	Serial.write(oldCol & 0xFF);
	Serial.write(newCol >> 8);
	Serial.write(newCol & 0xFF);

	return (getResponse() == 6);
}

uint8_t drawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0xCD);
	Serial.write(x >> 8);
	Serial.write(x & 0xFF);
	Serial.write(y >> 8);
	Serial.write(y & 0xFF);
	Serial.write(r >> 8);
	Serial.write(r & 0xFF);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint8_t fillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0xCC);
	Serial.write(x >> 8);
	Serial.write(x & 0xFF);
	Serial.write(y >> 8);
	Serial.write(y & 0xFF);
	Serial.write(r >> 8);
	Serial.write(r & 0xFF);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint8_t drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0xD2);
	Serial.write(x1 >> 8);
	Serial.write(x1 & 0xFF);
	Serial.write(y1 >> 8);
	Serial.write(y1 & 0xFF);
	Serial.write(x2 >> 8);
	Serial.write(x2 & 0xFF);
	Serial.write(y2 >> 8);
	Serial.write(y2 & 0xFF);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint8_t drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0xCF);
	Serial.write(x >> 8);
	Serial.write(x & 0xFF);
	Serial.write(y >> 8);
	Serial.write(y & 0xFF);
	Serial.write((x + width) >> 8);
	Serial.write((x + width) & 0xFF);
	Serial.write((y + height) >> 8);
	Serial.write((y + height) & 0xFF);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint8_t fillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0xCE);
	Serial.write(x >> 8);
	Serial.write(x & 0xFF);
	Serial.write(y >> 8);
	Serial.write(y & 0xFF);
	Serial.write((x + width) >> 8);
	Serial.write((x + width) & 0xFF);
	Serial.write((y + height) >> 8);
	Serial.write((y + height) & 0xFF);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint8_t drawPolyline(uint16_t n, uint16_t* xCoords, uint16_t* yCoords, uint16_t color) {
	uint32_t index = 0;
	Serial.write(0x00);
	Serial.write(0x05);
	Serial.write(n >> 8);
	Serial.write(n & 0xFF);
	while (index < n) {
		Serial.write(xCoords[index] >> 8);
		Serial.write(xCoords[index] & 0xFF);
		++index;
	}
	index = 0;
	while (index < n) {
		Serial.write(yCoords[index] >> 8);
		Serial.write(yCoords[index] & 0xFF);
		++index;
	}

	return (getResponse() == 6);
}

uint8_t drawPolygon(uint16_t n, uint16_t* xCoords, uint16_t* yCoords, uint16_t color) {
	uint32_t index = 0;
	Serial.write(0x00);
	Serial.write(0x04);
	Serial.write(n >> 8);
	Serial.write(n & 0xFF);
	while (index < n) {
		Serial.write(xCoords[index] >> 8);
		Serial.write(xCoords[index] & 0xFF);
		++index;
	}
	index = 0;
	while (index < n) {
		Serial.write(yCoords[index] >> 8);
		Serial.write(yCoords[index] & 0xFF);
		++index;
	}

	return (getResponse() == 6);
}

uint8_t drawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0xC9);
	Serial.write(x1 >> 8);
	Serial.write(x1 & 0xFF);
	Serial.write(y1 >> 8);
	Serial.write(y1 & 0xFF);
	Serial.write(x2 >> 8);
	Serial.write(x2 & 0xFF);
	Serial.write(y2 >> 8);
	Serial.write(y2 & 0xFF);
	Serial.write(x3 >> 8);
	Serial.write(x3 & 0xFF);
	Serial.write(y3 >> 8);
	Serial.write(y3 & 0xFF);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint32_t calculateOrbit(uint16_t angle, uint16_t distance) {
	uint8_t ACK;
	uint32_t x, y;

	Serial.write(0x00);
	Serial.write(0x03);
	Serial.write(angle >> 8);
	Serial.write(angle & 0xFF);
	Serial.write(distance >> 8);
	Serial.write(distance & 0xFF);

	while (!Serial.available()) delay(1);
	ACK = Serial.read();
	x = Serial.read();
	x += Serial.read();
	y = Serial.read();
	y += Serial.read();

	x = x << 8;

	if (!ACK) return 0;
	return x + y;
}

uint8_t putPixel(uint16_t x, uint16_t y, uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0xCB);
	Serial.write(x >> 8);
	Serial.write(x & 0xFF);
	Serial.write(y >> 8);
	Serial.write(y & 0xFF);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint16_t readPixel(uint16_t x, uint16_t y) {
	uint8_t ACK;
	uint16_t color;

	Serial.write(0xFF);
	Serial.write(0xCA);
	Serial.write(x >> 8);
	Serial.write(x & 0xFF);
	Serial.write(y >> 8);
	Serial.write(y & 0xFF);

	while (!Serial.available()) delay(1);
	ACK = Serial.read();
	color = Serial.read() << 8;
	color += Serial.read();

	return color;
}

uint8_t moveOrigin(uint16_t x, uint16_t y) {
	Serial.write(0xFF);
	Serial.write(0xD6);
	Serial.write(x >> 8);
	Serial.write(x & 0xFF);
	Serial.write(y >> 8);
	Serial.write(y & 0xFF);

	return (getResponse() == 6);
}

uint8_t setBG(uint16_t c) {
  Serial.write(0xFF);
  Serial.write(0x6E);
  Serial.write(c >> 8);
  Serial.write(c & 0xFF);

  return (getResponse() == 6);
}

uint8_t setOutlineColor(uint16_t color) {
	Serial.write(0xFF);
	Serial.write(0x67);
	Serial.write(color >> 8);
	Serial.write(color & 0xFF);

	return (getResponse() == 6);
}

uint8_t setContrast(uint8_t lvl) {
    if (lvl < 0 || lvl > 15) return 0;
    Serial.write(0xFF);
    Serial.write(0x66);

    Serial.write(0);
    Serial.write(lvl);

    return (getResponse() == 6);
}

uint16_t setFrameDelay(uint16_t ms) {
	uint8_t ACK;
	uint16_t val;

	Serial.write(0xFF);
	Serial.write(0x69);
	Serial.write(ms >> 8);
	Serial.write(ms & 0xFF);

	while (!Serial.available()) delay(1);
	ACK = Serial.read();
	val = Serial.read() << 8;
	val += Serial.read();

	return val;
}

uint8_t setLinePattern(uint16_t pattern) {
	Serial.write(0xFF);
	Serial.write(0x65);
	Serial.write(pattern >> 8);
	Serial.write(pattern & 0xFF);

	return (getResponse() == 6);
}

uint8_t setScreenMode(uint8_t mode) {
	Serial.write(0xFF);
	Serial.write(0x68);
	Serial.write(0);
	Serial.write(mode);

	return (getResponse() == 6);
}

uint8_t setGraphicsParams(uint16_t function, uint16_t val) {
	Serial.write(0xFF);
	Serial.write(0xD8);
	Serial.write(0);
	Serial.write(function & 0xFF);
	Serial.write(val >> 8);
	Serial.write(val & 0xFF);

	return (getResponse() == 6);
}

/*****************************
 * OTHER IMPORTANT FUNCTIONS *
 *****************************/
uint8_t turnOffScreenSaver() {
  Serial.write(0x00);
  Serial.write(0x0C);
  Serial.write(0);
  Serial.write(0);

  return (getResponse() == 6);
}
