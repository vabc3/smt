#include <stdint.h>

extern int 	PipcdInit();
extern void PipcdShow(const uint8_t data[]);
extern void PipcdDraw(const uint8_t data[]);
extern void PipcdLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
extern void PipcdRefresh();
extern void	PipcdClear();

