#ifndef __PLAY_MUSIC_H__
#define __PLAY_MUSIC_H__

#define DEFAULT_VOLUME 100

void InitMusic();
void PlayMusic(const int* pMusicNotes, uint8_t tempo);

#endif // __PLAY_MUSIC_H__