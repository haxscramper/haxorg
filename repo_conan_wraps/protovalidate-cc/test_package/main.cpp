#include <buf/validate/validate.pb.h>
#include <buf/validate/validator.h>

int main() {
    buf::validate::FieldRules rules;
    rules.set_required(true);

    return rules.required() ? 0 : 1;
}
