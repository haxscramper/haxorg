def is_targeted_function(func):
  (0 < func.count) and
  (any(func.filenames[]; test(".*?base_lexer_gen\\.cpp$")) | not)
  ;

def filter_raw_json:
  {
    data: .data | map({
      functions: 
        .functions 
        | map(select(is_targeted_function(.))),
      files: 
        .files 
        | map(
            . as $file 
            | select(
                (
                  ($file.filename | test("Map.(cc|h|cpp|hpp)$")) or
                  ($file.filename | contains("thirdparty"))
                )
                | not)) 
        | map({
            filename, 
            segments, 
            summary, 
            branches, 
            expansions,
          }),
      totals,
    }),
    type, 
    version,
  };
