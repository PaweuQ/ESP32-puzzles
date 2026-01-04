#include <MD_MAX72xx.h>
#include <SPI.h>

/* ========= HARDWARE ========= */
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES   4
#define CS_PIN        5

MD_MAX72XX mx(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

/* ========= TIMING ========= */
#define UNIT_DELAY      25
#define HEARTBEAT_DELAY (60)
#define PACMAN_DELAY    (4 * UNIT_DELAY)
#define INVADER_DELAY   (6 * UNIT_DELAY)

/* ========= ILOŚĆ POWTÓRZEŃ ========= */
#define HEARTBEAT_REPEATS  3
#define PACMAN_REPEATS     1
#define INVADER_REPEATS    1
#define BOUNCEBALL_REPEATS 1


#define BOUNCE_DELAY        (60)
#define BOUNCE_HITS_PER_RUN 50   // ile odbić = 1 cykl animacji

uint32_t prevTimeAnim = 0;

/* ========= NARZĘDZIA ========= */
void resetMatrix(void)
{
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
  prevTimeAnim = 0;
}

/* ========= HEARTBEAT ========= */
bool graphicHeartbeat(bool bInit)
{
  #define BASELINE_ROW 4
  static uint8_t state, r, c;
  static bool bPoint;

  if (bInit)
  {
    resetMatrix();
    state = 0;
    r = BASELINE_ROW;
    c = mx.getColumnCount() - 1;
    bPoint = true;
    bInit = false;
  }

  if (millis() - prevTimeAnim < HEARTBEAT_DELAY) return false;
  prevTimeAnim = millis();

  mx.setPoint(r, c, bPoint);

  switch (state)
  {
    case 0: if (c == mx.getColumnCount()/2 + COL_SIZE) state = 1; c--; break;
    case 1: if (r != 0) { r--; c--; } else state = 2; break;
    case 2: if (r != ROW_SIZE-1) { r++; c--; } else state = 3; break;
    case 3: if (r != BASELINE_ROW) { r--; c--; } else state = 4; break;
    case 4:
      if (c == 0) { c = mx.getColumnCount()-1; state = 0; return true; }
      c--;
      break;
  }
  return false;
}

/* ========= PACMAN ========= */
bool graphicPacman(bool bInit)
{
  #define FRAMES 4
  #define W 18

  const uint8_t pac[FRAMES][W] = {
    {0x3c,0x7e,0x7e,0xff,0xe7,0xc3,0x81,0,0,0,0,0xfe,0x7b,0xf3,0x7f,0xfb,0x73,0xfe},
    {0x3c,0x7e,0xff,0xff,0xe7,0xe7,0x42,0,0,0,0,0xfe,0x7b,0xf3,0x7f,0xfb,0x73,0xfe},
    {0x3c,0x7e,0xff,0xff,0xff,0xe7,0x66,0x24,0,0,0,0xfe,0x7b,0xf3,0x7f,0xfb,0x73,0xfe},
    {0x3c,0x7e,0xff,0xff,0xff,0xff,0x7e,0x3c,0,0,0,0xfe,0x7b,0xf3,0x7f,0xfb,0x73,0xfe}
  };

  static int16_t idx;
  static uint8_t frame, df;

  if (bInit)
  {
    resetMatrix();
    idx = -W;
    frame = 0;
    df = 1;
    bInit = false;
  }

  if (millis() - prevTimeAnim < PACMAN_DELAY) return false;
  prevTimeAnim = millis();

  mx.clear();
  idx++;
  for (uint8_t i=0; i<W; i++)
    mx.setColumn(idx-W+i, pac[frame][i]);

  frame += df;
  if (frame == 0 || frame == FRAMES-1) df = -df;

  return (idx > mx.getColumnCount() + W);
}

/* ========= INVADER ========= */
bool graphicInvader(bool bInit)
{
  const uint8_t inv1[] = {0x0e,0x98,0x7d,0x36,0x3c};
  const uint8_t inv2[] = {0x70,0x18,0x7d,0xb6,0x3c};
  const uint8_t size = sizeof(inv1);

  static int8_t idx;
  static bool type;

  if (bInit)
  {
    resetMatrix();
    idx = -size;
    type = false;
    bInit = false;
  }

  if (millis() - prevTimeAnim < INVADER_DELAY) return false;
  prevTimeAnim = millis();

  mx.clear();
  for (uint8_t i=0; i<size; i++)
  {
    mx.setColumn(idx-size+i, type ? inv1[i] : inv2[i]);
    mx.setColumn(idx+size-i-1, type ? inv1[i] : inv2[i]);
  }

  idx++;
  type = !type;

  return (idx > mx.getColumnCount() + size);
}

/* ========= BOUNCE BALL ========= */
bool graphicBounceBall(bool bInit)
{
  static int8_t x, y;
  static int8_t dx, dy;
  static uint8_t hits;

  const uint8_t WIDTH  = mx.getColumnCount();
  const uint8_t HEIGHT = ROW_SIZE;

  if (bInit)
  {
    resetMatrix();

    x = random(WIDTH);
    y = random(HEIGHT);

    dx = random(0, 2) ? 1 : -1;
    dy = random(0, 2) ? 1 : -1;

    hits = 0;
    bInit = false;
  }

  if (millis() - prevTimeAnim < BOUNCE_DELAY)
    return false;
  prevTimeAnim = millis();

  mx.clear();
  mx.setPoint(y, x, true);

  x += dx;
  y += dy;

  bool bounced = false;

  if (x <= 0 || x >= WIDTH - 1)
  {
    dx = -dx;
    bounced = true;
  }

  if (y <= 0 || y >= HEIGHT - 1)
  {
    dy = -dy;
    bounced = true;
  }

  if (bounced)
    hits++;

  // po określonej liczbie odbić uznajemy animację za zakończoną
  if (hits >= BOUNCE_HITS_PER_RUN)
    return true;

  return false;
}


/* ========= LOOP ========= */
void setup()
{
  mx.begin();
}

void loop()
{
  static uint8_t state = 0;
  static uint8_t count = 0;
  static bool init = true;

  bool done = false;

  switch (state)
  {
    case 0: done = graphicHeartbeat(init);   break;
    case 1: done = graphicPacman(init);      break;
    case 2: done = graphicInvader(init);     break;
    case 3: done = graphicBounceBall(init);  break;
  }

  init = false;

  if (done)
  {
    count++;
    init = true;
  }

  uint8_t limits[] = {
    HEARTBEAT_REPEATS,
    PACMAN_REPEATS,
    INVADER_REPEATS,
    BOUNCEBALL_REPEATS
  };

  if (count >= limits[state])
  {
    count = 0;
    state = (state + 1) % 4;
    init = true;
  }
}
