#include "NumericSelector.h"

NumericSelector::NumericSelector(MenuItem* parent, const __FlashStringHelper* text, uint8_t& variable, uint8_t min, uint8_t max) : MenuItem(parent, text), variable(variable) {
    this->min = min;
    this->max = max;

    oldValue = variable;
};

uint8_t NumericSelector::getValue() { return variable; }
uint8_t NumericSelector::getMin()   { return min; }
uint8_t NumericSelector::getMax()   { return max; }

const char* NumericSelector::getSecondaryText() {
    sprintf(valueStr, "<%d>", variable);

    return valueStr;
}

int NumericSelector::activate() {
    oldValue = variable;

    return 1;
}

int NumericSelector::deactivate() {
    variable = oldValue;

    return 1;
}

void NumericSelector::doNext() {
    variable++;

    if(variable > max)
        variable = min;
}
void NumericSelector::doPrev() {
    variable--;

    if(variable < min)
        variable = max;
}

MenuItem* NumericSelector::action() { 
    return this->getParent(); 
}