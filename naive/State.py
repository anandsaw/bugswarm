from enum import Enum


class State(Enum):
    NOT_IN_INLINED_FUNCTION = 0
    IN_INLINED_FUNCTION = 1
    FOUND_FUNCTION = 2
