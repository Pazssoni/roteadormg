/*
 * Monitor.h
 *
 *  Created on: 11 de ago. de 2025
 *      Author: Aluno
 */

#ifndef __PROJETOROTEAMENTO_MONITOR_H_
#define __PROJETOROTEAMENTO_MONITOR_H_

#include <omnetpp.h>

using namespace omnetpp;

class Monitor : public cSimpleModule
{
  protected:
    virtual void finish() override;
};
#endif
