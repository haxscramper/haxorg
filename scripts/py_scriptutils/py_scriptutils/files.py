import os
from typing import Callable, TypeVar
import pickle

T = TypeVar('T')

def IsNewInput(input_path: str, output_path: str):
    should_execute = False
    
    # Check if the files exist
    input_exists = os.path.exists(input_path)
    output_exists = os.path.exists(output_path)

    # If input exists but output doesn't, execute the body
    if input_exists and not output_exists:
        should_execute = True

    # If both exist, check their modification times
    elif input_exists and output_exists:
        input_mtime = os.path.getmtime(input_path)
        output_mtime = os.path.getmtime(output_path)
        
        # If input was modified after output, execute the body
        if input_mtime > output_mtime:
            should_execute = True
    
    return should_execute


def pickle_or_new(input_path: str, output_path: str, builder_cb: Callable[[str], T]) -> T:
    if IsNewInput(input_path, output_path):
        value: T = builder_cb(input_path)
        with open(output_path, "wb") as file:
            pickle.dump(value, file)

        return value

    else:
        with open(output_path, "rb") as file:
            return pickle.load(file)
        
