from beartype import beartype


@beartype
def abbreviate_token_name(token: str) -> str:
    "Create shorter representation of the pygments token type"
    # Remove the base "Token" from the token type
    token_path = str(token).split('.')[1:]

    # Take the first letter of each part of the token type
    abbreviation = ''.join(part[0] for part in token_path).lower()

    return abbreviation
