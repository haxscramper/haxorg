from repo_py_orchestrate.codegen_config import org_codegen_data


def test_org_codegen_data_run():
    org_codegen_data.get_enums()
    org_codegen_data.get_shared_sem_enums()
