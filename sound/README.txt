https://archive.org/download/Greatest_Speeches_of_the_20th_Century

Resample to mono 8k PCM
$ ffmpeg -i ResignationAddress-1974.ogg -f s16le -acodec pcm_s16le -ac 1 -ar 8k ResignationAddress-1974.pcm
