from typing import Any


class HasAnyAttr():
    def __getattribute__(self, name: str):
        return HasAnyAttr()
    
    def __getattr__(self, name: str):
        return HasAnyAttr()
    
    def __getitem__(self, key):
        return HasAnyAttr()
    
    def __call__(self, *args, **kwargs):
        return HasAnyAttr()
    
    def __bool__(self):
        return True
    
    def __str__(self):
        return "HasAnyAttr()"
    
    def __repr__(self):
        return "HasAnyAttr()"
