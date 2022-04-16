#pragma once

extern int Random(void);
extern void DrawIcons(int scrw, int scrh);
extern void ScrMove(std::atomic<bool>& quit_flag);
extern void GTDesktop(void);
extern void Glitch(void);
