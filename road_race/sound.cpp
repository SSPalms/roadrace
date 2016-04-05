#include <sound.h>
#include <roadrace.h>
#include <gui.h>
#include <QString>
#include <QFile>
#include <QObject>
#include <QtMultimedia/QSoundEffect>
#include <QMessageBox>
using namespace std;

Sound *Sound::instance_ = NULL;

Sound& Sound::instance() {
    if ( instance_ == NULL ) {
        instance_ = new Sound;
    }
    return *instance_;
}

void Sound::playSound(QString s, float volume)
{
    effect = new QSoundEffect;
    effect->setSource(QUrl::fromLocalFile(s));
    effect->setVolume(volume * vol);
    effect->play();
}

void Sound::playSoundTrack()
{
    effect = new QSoundEffect;
    effect->setSource(QUrl::fromLocalFile(":/music.wav"));
    effect->setVolume(.65f * vol);
    effect->setLoopCount(QSoundEffect::Infinite);
    effect->play();
}

void Sound::updateVolume()
{
    int i = GuiManager::instance().getUi()->volumeSlider->value();
    vol = i;
}
