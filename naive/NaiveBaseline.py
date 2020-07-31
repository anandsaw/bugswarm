from pygments.token import Token
from pygments.lexers.c_cpp import CFamilyLexer
import os
from State import State




def parse_file(path, functions):
    try:
        with open(path, "r") as f:
            content = f.read()
            lexer = CFamilyLexer(encoding='utf-8')
            tokens = lexer.get_tokens(content)
            return _process_tokens(tokens)
    except:
        return 0, ""


def _process_tokens(tokens):
    function_to_token_list = {}
    current_token_list = []
    current_state = State.NOT_IN_INLINED_FUNCTION
    current_function_name = ""
    line_count = 6
    for token in tokens:
        if current_state == State.FOUND_FUNCTION:
            current_state = State.IN_INLINED_FUNCTION
        if token[0] == Token.Literal.String and str.startswith(token[1], "function_inlined:"):
            function_name = str.replace(token[1], "function_inlined: ", "")
            if function_name not in function_to_token_list:
                function_to_token_list[function_name] = []
            line_count = 6
            print(function_to_token_list)
            print(function_name)
            if current_state == State.NOT_IN_INLINED_FUNCTION:
                current_state = State.IN_INLINED_FUNCTION
                current_function_name = function_name
            print(current_state)
        #     elif current_state == State.IN_INLINED_FUNCTION:
        #         rep_list = function_to_token_list.get(current_function_name)
        #         rep_list.append(current_token_list.copy())
        #         current_function_name = function_name
        #     current_token_list = []
        #     current_state = State.FOUND_FUNCTION
        # if token[0] == Token.Text and token[1] == '\n':
        #     line_count -= 1
        #     print(line_count)
        # if line_count == 0:
        #     rep_list = function_to_token_list.get(current_function_name)
        #     rep_list.append(current_token_list.copy())
        #     current_token_list = []
        #     current_state = State.NOT_IN_INLINED_FUNCTION
        # if current_state == State.IN_INLINED_FUNCTION:
        #     current_token_list.append(token)


def read_function_list(path):
    functions = set()
    with open(path, "r") as f:
        for line in f:
            functions.add(line)
    return functions


def collect_file_paths(base_path):
    paths = []
    for root,dirs,files in os.walk(base_path):
        for file in files:
            if file.endswith(".c") and file == "run_decom_puts.c":
                paths.append(os.path.join(os.path.abspath(root), file))
    return paths


def main():
    functions = read_function_list("./pos-labels.txt")
    decompiled_files = collect_file_paths("./")
    for file in decompiled_files:
        print(file)
        parse_file(file, functions)


if __name__ == '__main__':
    main()
