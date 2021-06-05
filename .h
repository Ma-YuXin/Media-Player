#ifndef LYRIC_H
#define LYRIC_H
#include<QFile>
#include<QDebug>
#include<QStringList>
class Lyric
{
public:
    Lyric();
QString m_LyricDir;
QString m_lyricPath;
    void getCurrentSongLyric(QStringList &LyricList,QMap<qint64, qint64> &LyricShow);
};

#endif // LYRIC_H
