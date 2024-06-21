//
// Created by sjr on 4/1/24.
//

#include "programs/program_manager.hpp"

#include <IRremote.hpp>
#include "ir.hpp"
#include "matrix_manager.hpp"

void RemoteManager::init() {
    IrReceiver.begin(IR_PIN, true);
}

void RemoteManager::TranslateIR(uint32_t code) {

    switch(code)  {
        case 0xFFA25D: Serial.println("POWER"); break;
        case 0xFFE21D:
            Serial.println("FUNC/STOP");
            pm.NextProgram();
            
            break;
        case 0xFF629D:
            Serial.println("VOL+");
            pm.CurrentProgram()->VolUp();
            break;
        case 0xFF22DD:
            Serial.println("FAST BACK");
            pm.CurrentProgram()->Prev();
            break;
        case 0xFF02FD:
            Serial.println("PAUSE");
            this->paused = !this->paused;
            break;
        case 0xFFC23D:
            Serial.println("FAST FORWARD");
            pm.CurrentProgram()->Next();

            break;
        case 0xFFE01F:
            Serial.println("DOWN");
            pm.CurrentProgram()->Down();

            break;
        case 0xFFA857:
            Serial.println("VOL-");
            pm.CurrentProgram()->VolDown();

            break;
        case 0xFF906F:
            Serial.println("UP");
            pm.CurrentProgram()->VolUp();

            break;
        case 0xFF9867:
            Serial.println("EQ");
            pm.CurrentProgram()->Eq();

            break;
        case 0xFFB04F:
            Serial.println("ST/REPT");
            break;
        case 0xFF6897:
            Serial.println("0");
            pm.CurrentProgram()->Number(0);

            break;
        case 0xFF30CF:
            Serial.println("1");
            pm.CurrentProgram()->Number(1);
            break;
        case 0xFF18E7:
            Serial.println("2");
            pm.CurrentProgram()->Number(2);
            break;
        case 0xFF7A85:
            Serial.println("3");
            pm.CurrentProgram()->Number(3);
            break;
        case 0xFF10EF:
            Serial.println("4");
            pm.CurrentProgram()->Number(4);

            break;
        case 0xFF38C7:
            Serial.println("5");
            pm.CurrentProgram()->Number(5);
            break;
        case 0xFF5AA5:
            Serial.println("6");
            pm.CurrentProgram()->Number(6);
            break;
        case 0xFF42BD:
            Serial.println("7");
            pm.CurrentProgram()->Number(7);
            break;
        case 0xFF4AB5:
            Serial.println("8");
            pm.CurrentProgram()->Number(8);
            break;
        case 0xFF52AD:
            Serial.println("9");
            pm.CurrentProgram()->Number(9);
            break;

        case 0xFFFFFFFF:
            Serial.println(" REPEAT");
            break;

        default:
            Serial.print("Unknown:");
            Serial.println(code);
            break;

    }
}

bool RemoteManager::ProcessIRAndCheckIfShouldContinue() {
    if (IrReceiver.decode()) // have we received an IR signal?`
    {
        uint32_t code = bitreverse32Bit(IrReceiver.decodedIRData.decodedRawData);

        IrReceiver.resume(); // receive the next value

        mm.SetIcon(' ');
        this->TranslateIR(code);

    }

    if (!IrReceiver.isIdle()) {
        return false;
    }

    return true;
}

bool RemoteManager::IsPaused() {
    return this->paused;
}

RemoteManager rm = RemoteManager();