import py_haxorg.pyhaxorg as org
from py_textlayout.py_textlayout_wrap import *
from py_haxorg.pyhaxorg import OrgSemKind as osk
import re
from py_scriptutils.script_logging import log


class ExporterBase:

    def evalTop(self, node: org.Org):
        return self.exp.evalTop(node)
    
    def eval(self, node: org.Org):
        return self.exp.eval(node)

    def __init__(self, derived):
        self.exp = org.ExporterPython()

        direct_mappings = {
            "visitAnyIdAround": self.exp.setVisitAnyIdAround,
            "visitAnyIdIn": self.exp.setVisitAnyIdIn,
            "visitAnyField": self.exp.setVisitAnyField,
            "evalTopCb": self.exp.setEvalTopCb,
            "setPushVisitAnyId": self.exp.setPushVisitAnyId,
            "setPopVisitAnyId": self.exp.setPopVisitAnyId,
            "visitAnyHook": self.exp.setVisitAnyHookCb,
            "newOrg": self.exp.setNewAnyOrgRes,
            "newLeaf": self.exp.setNewAnyLeafRes,
        }
        for method_name, setter in direct_mappings.items():
            if hasattr(derived, method_name):
                setter(getattr(type(derived), method_name))

        prefix_to_setter_with_kind = [
            (r"visit(.*)", self.exp.setVisitIdInCb),
            (r"eval(.*)", self.exp.setEvalIdIn),
            (r"visit(.*?)Around", self.exp.setVisitIdAround),
            (r"eval(.*?)Around", self.exp.setEvalIdAround),
            (r"visit(.*?)LeafField", self.exp.setVisitLeafField),
            (r"eval(.*?)LeafField", self.exp.setEvalLeafField),
            (r"visit(.*?)OrgField", self.exp.setVisitOrgField),
            (r"eval(.*?)OrgField", self.exp.setEvalOrgField),
            (r"setPushVisitId", self.exp.setPushVisitId),
            (r"setPopVisitIdCb", self.exp.setPopVisitIdCb),
            (r"visit(.*?)Hook", self.exp.setVisitIdHook),
            (r"newOrg(.*)", self.exp.setNewOrgRes),
            (r"newLeaf(.*)", self.exp.setNewLeafRes),
        ]

        for method_name in dir(derived):
            if method_name.startswith("__") or method_name in direct_mappings or method_name in ["evalTop"]:
                continue

            for (prefix, setter) in prefix_to_setter_with_kind:
                match = re.match(prefix, method_name)
                if match:
                    kind_str = match.group(1)
                    kind_enum = getattr(org.OrgSemKind, kind_str, None)

                    if len(kind_str) == 0:
                        continue

                    if not kind_enum:
                        kind_enum = getattr(org.LeafFieldType, kind_str, None)

                    if kind_enum:
                        setter(kind_enum, getattr(type(derived), method_name))
                        break

                    else:
                        log("haxorg.export").warning(
                            f"Method {method_name} (kind {kind_str}) of {type(derived)} is not a kind enum visitor, not OrgSemKind, not LeafFieldType"
                        )

        self.exp.setSelf(self)
