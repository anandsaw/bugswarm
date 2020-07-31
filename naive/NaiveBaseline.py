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
            function_to_token_list = split_tokens(tokens)
            return process_functions(function_to_token_list)
    except:
        return 0, ""


def split_tokens(tokens):
    function_to_token_list = {}
    current_token_list = []
    current_state = State.NOT_IN_INLINED_FUNCTION
    current_function_name = ""
    line_count = 6
    for token in tokens:
        if current_state == State.FOUND_FUNCTION and token[0] == Token.Text and token[1] == '\n':
            # print("setting state")
            current_state = State.IN_INLINED_FUNCTION
            # print(current_state)
            # print(token)
            # print(line_count)
        if token[0] == Token.Literal.String and str.startswith(token[1], "function_inlined:"):
            function_name = str.replace(token[1], "function_inlined: ", "")
            if function_name not in function_to_token_list:
                function_to_token_list[function_name] = []
            line_count = 5
            # print(function_to_token_list)
            # print(function_name)
            if current_state == State.IN_INLINED_FUNCTION:
                rep_list = function_to_token_list.get(current_function_name)
                rep_list.append(current_token_list.copy())
            current_function_name = function_name
            current_token_list = []
            current_state = State.FOUND_FUNCTION
            # print(line_count)
        if token[0] == Token.Text and token[1] == '\n' and current_state == State.IN_INLINED_FUNCTION:
            # print("reducing line")
            line_count -= 1
        if line_count == 0 and current_state == State.IN_INLINED_FUNCTION:
            rep_list = function_to_token_list.get(current_function_name)
            rep_list.append(current_token_list.copy())
            current_token_list = []
            current_state = State.NOT_IN_INLINED_FUNCTION

        if current_state == State.IN_INLINED_FUNCTION:
            # print("adding to list")
            current_token_list.append(token)
        # print(current_state)
    # print(function_to_token_list)
    return function_to_token_list


def process_functions(function_to_token_list):
    for function in function_to_token_list:
        print(function)
        rep_list = function_to_token_list[function]
        for rep in rep_list:
            print("REP")
            filtered_list = []
            name_count = 0
            for token in rep:
                print(token)
                if token[0] == Token.Text:
                    continue
                if token[0] == Token.Name:
                    t = Token(token[0], "name" + str(name_count))
                    name_count += 1
                # if token[0] in Token.Literal.Number:
                #     token[0] = Token.Literal.Number
                #     token[1] = "number"
                filtered_list.append(token)
            print("filtered")
            for token in filtered_list:
                print(token)

    return []



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
        function_reps = parse_file(file, functions)
        # for function in function_reps:
        #     print("FUNCTION: " + function)
        #     rep_list = function_reps.get(function)
        #
        #     for rep in rep_list:
        #         print("REP:")
        #         str_rep = ""
        #         for tok in rep:
        #             str_rep += tok[1]
        #         print(str_rep)


if __name__ == '__main__':
    main()
