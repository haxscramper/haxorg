
std::string BaseLexerImpl::state_name(int state) {
    switch(state) {
        case 0: return "COMMAND";
        case 1: return "COMMAND_TEXT";
        case 2: return "COMMAND_OPTS";
        case 3: return "COMMAND_EXAMPLE";
        case 4: return "COMMAND_SRC";
        case 5: return "BODY_SRC";
        default: return std::to_string(state);
    }
}
