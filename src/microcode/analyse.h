#ifndef ANALYSE_H
#define ANALYSE_H

struct Parser;
struct VMCoreGen;

void InitAnalysis();
void Analyse(struct Parser* parser, struct VMCoreGen* core);

#endif