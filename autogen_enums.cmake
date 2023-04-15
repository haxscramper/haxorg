
add_custom_command(
  OUTPUT ${AUTOGEN_BUILD_DIR}/enum.json
  COMMAND "${SCRIPT_DIR}/generate_type_info.py"
          "${BASE}/src/types/enums.hpp" "${AUTOGEN_BUILD_DIR}/enum.json"
  DEPENDS "${SCRIPT_DIR}/generate_type_info.py"
          "${BASE}/src/types/enums.hpp"
  COMMENT "Generating enum reflection information")

add_custom_command(
  OUTPUT "${AUTOGEN_BUILD_DIR}/autogen_enum_help.hpp"
         "${AUTOGEN_BUILD_DIR}/autogen_enum_help.cpp"
  COMMAND
    "${SCRIPT_DIR}/generate_type_aux.py" #
    "${AUTOGEN_BUILD_DIR}/enum.json" #
    "${AUTOGEN_BUILD_DIR}/autogen_enum_help.hpp" #
    "${AUTOGEN_BUILD_DIR}/autogen_enum_help.cpp" #
  DEPENDS "${SCRIPT_DIR}/generate_type_aux.py"
          "${AUTOGEN_BUILD_DIR}/enum.json"
  COMMENT "Generating enum reflection wrappers")

add_custom_target(
  autogen_enums DEPENDS "${AUTOGEN_BUILD_DIR}/autogen_enum_help.hpp"
                          "${AUTOGEN_BUILD_DIR}/autogen_enum_help.cpp")
