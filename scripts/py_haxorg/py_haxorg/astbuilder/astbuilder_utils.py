def pascal_case(s: str) -> str:
    """
    Capitalize first character in the string, don't change others.
    Use this instead of `.capitalize()` for the identifiers -- the
    str() function also turns all other characters to lowercase.
    """
    return s[0].upper() + s[1:] if s else ""
