import lldb

from hstd_py_lib.debug_utils.format_base import FormatterMemoryError, SyntheticProvider


class PyObjectProvider(SyntheticProvider):
    # Match objects and single pointers, but not PyObject **.
    type_regex = (
        r"^(?:const[ \t]+)?(?:struct[ \t]+)?(?:PyObject|_object)"
        r"(?:[ \t]+const)?"
        r"(?:[ \t]*\*(?:[ \t]*const)?)?"
        r"(?:[ \t]*&)?[ \t]*$"
    )
    extract_as_leaf = True

    def summary_text(self) -> str:
        source = self.value

        if source.GetType().IsPointerType():
            if source.GetValueAsUnsigned() == 0:
                return "<null>"

            source = source.Dereference().GetNonSyntheticValue()

        name = source.GetChildMemberWithName("ob_type").GetChildMemberWithName("tp_name")

        if not name.IsValid():
            raise RuntimeError("Cannot resolve PyObject.ob_type->tp_name")

        error = name.GetError()
        if error.Fail():
            raise FormatterMemoryError(error.GetCString())

        address = name.GetValueAsUnsigned()
        if address == 0:
            raise RuntimeError("PyObject.ob_type->tp_name is null")

        error = lldb.SBError()
        type_name = source.GetProcess().ReadCStringFromMemory(
            address,
            self.settings.formatter_max_string,
            error,
        )

        if error.Fail():
            raise FormatterMemoryError(error.GetCString())

        return type_name
