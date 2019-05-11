//
// Created by swift on 2019/5/10.
//

#ifndef SANDHOOK_NH_UNIT_H
#define SANDHOOK_NH_UNIT_H

#include <malloc.h>
#include "../includes/base.h"

namespace SandHook {
    namespace Asm {

        template <typename Raw>
        class Unit {
        public:

            Unit() {
                if (unitType() != UnitVoid) {
                    raw = reinterpret_cast<Raw *>(malloc(size()));
                    memset(raw, 0, size());
                    auto_alloc = true;
                }
            }

            Unit<Raw>(Raw *raw) : raw(raw) {}

            Unit<Raw>(Raw raw) {
                Unit();
                *this->raw = raw;
            }

            virtual void* getPC() {
                return auto_alloc ? nullptr : raw;
            }

            inline Addr getVPC() {
                return vPC;
            }

            inline void setVPC(Addr vPC) {
                this->vPC = vPC;
            }

            inline Raw* get() const {
                return raw;
            }

            inline void set(Raw raw) const {
                *this->raw = raw;
            }

            inline void set(Raw* raw) {
                if (auto_alloc) {
                    free(this->raw);
                    auto_alloc = false;
                }
                this->raw = raw;
            }

            inline void copy(void* dest) {
                memcpy(dest, getPC(), size());
            }


            inline void move(Raw* dest) {
                memcpy(dest, raw, size());
                if (auto_alloc) {
                    free(raw);
                    auto_alloc = false;
                }
                raw = dest;
            }

            virtual UnitType unitType() {
                return UnitType::UnitUnknow;
            };

            virtual U32 size() {
                return sizeof(Raw);
            }

            virtual ~Unit() {
                if (auto_alloc) {
                    free(raw);
                }
            }

        private:
            Raw* raw;
            Addr vPC;
            bool auto_alloc = false;
        };

    }
}

#endif //SANDHOOK_NH_UNIT_H
