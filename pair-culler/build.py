from dataclasses import dataclass
from typing import List
from typing import Any


@dataclass
class Build:
    build_id: int
    job_list: List[Any]