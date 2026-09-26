#include <buf/validate/validate.pb.h>
#include <protovalidate/validator.h>

int main() {
    buf::validate::FieldConstraints constraints;
    constraints.set_required(true);

    return constraints.required() ? 0 : 1;
}
