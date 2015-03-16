#ifndef MenuItem_h
#define MenuItem_h

#include <Arduino.h>

//  Abstract class

class MenuItem {
    private:
        MenuItem* parent;

        const char* text;
        bool is_flash;
    public:
        MenuItem(MenuItem* parent, const __FlashStringHelper* text) { this->parent = parent;  setText(text); }

        virtual MenuItem* getParent() { return parent; }
        virtual void setParent(MenuItem* parent) { this->parent = parent; }

        virtual bool isTextFlash() { return is_flash; }
        virtual const char* getText() { return text; }
        virtual void  setText(const __FlashStringHelper* text) { this->is_flash = 1; this->text = reinterpret_cast<PGM_P>(text); }
        virtual void  setText(const char *text)                { this->is_flash = 0; this->text = text; }

        virtual const char* getSecondaryText() { return NULL; }

        virtual char getTypeId() = 0;

        // Called when the parent menu select the item

        /* Ritorna un booleano
           Se vero:  l'oggetto vorrà prendere il controllo
           Se false: l'oggetto ritornerà subito il controllo al padre.
        */
        virtual int activate() = 0;
        
        // Triggered when the current action is cancelled. (Back button pressed)
        // TODO: Determine what this function can return
        virtual int deactivate() = 0;
        
        // This events are triggerd only if the item is active.
        // ------

        // Called when event "next" is triggered
        // Usually this event is triggered when a down or right key is pressed
        virtual void doNext() = 0;

        // Called when event "prev" is triggered
        // Usually this event is triggered when up or left key is pressed
        virtual void doPrev() = 0;

        // Called when event "action" is triggered
        // Usually this event is triggered when center or ok key is pressed

        // Ritorna un puntatore ad un MenuItem che verrà attivato.
        // Se ritorna this o NULL, l'oggetto stesso manterrà il controllo.
        virtual MenuItem* action() = 0;

        virtual ~MenuItem() {}
};

#endif