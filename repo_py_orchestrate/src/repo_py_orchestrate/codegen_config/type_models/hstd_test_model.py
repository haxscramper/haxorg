from hstd_py_unidata.model_dsl import get_dsl_model

M = get_dsl_model("hstd.unidata_dsl.test")


class TrivialText(M.Class):
    text: str = M.Field(
        check=0 < M.This._Str.size(),
        message="text must not be empty",
    )
