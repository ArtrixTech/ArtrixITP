#ifndef ClientProcess_h
#define ClientProcess_h

#include "ArtrixITP.h"
#include "Arduino.h"
#include "StringProcess.h"

void ArtrixITP::CLIhandShake();

void ArtrixITP::CLI_REGDEV(Command cmd);
void ArtrixITP::CLI_ALIVE(Command cmd);

#endif
