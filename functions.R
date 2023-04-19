#' Read benchmarking data into a tibble
#'
#' @param filename the name of the benchmark output file
#'
#' @return a tibble
#' @export
#'

#    (compiler + table header + 5 data lines)
NROWS_PER_CHUNK <- 7

read_benchmark_data <- function(filename)
{
  checkmate::assert_file_exists(filename)
  text <- readLines(filename)
  # remove blank lines
  text <- text[!stringr::str_detect(text, "^\\s*$")]
  # remove divider lines
  text <- text[!stringr::str_starts(text, stringr::fixed("|---"))]
  
  # break into a list vectors; each vector has a length of NROWS_PER_CHUNK
  chunks <- split(text, ceiling(seq_along(text)/NROWS_PER_CHUNK))
  tibbles <- lapply(chunks, make_one_tibble)
  result <- dplyr::bind_rows(tibbles)
  result$func <-
    dplyr::case_when(result$func == "`handopt`"       ~ "handopt",
                     result$func == "`expression template use`" ~ "template",
                     result$func == "`only construct`"          ~ "constructor",
                     result$func == "`right fold`"              ~ "fold",
                     result$func == "`compiler expansion`"     ~ "naive")  
  dplyr::mutate(result,
                compiler = forcats::as_factor(compiler),
                func = forcats::as_factor(func))
}

make_one_tibble <- function(chunk)
{
  checkmate::assert_character(chunk)
  name <- chunk[1]
  data <- chunk[3:length(chunk)]
  d <- readr::read_delim(I(data),
                         delim="|",
                         trim_ws=TRUE,
                         col_names=c("dummy", "time", "speed", "fracerr", "total", "func"),
                         show_col_types=FALSE)
  d$compiler <- name
  dplyr::select(d, !dummy) |>
    dplyr::mutate(fracerr = readr::parse_number(fracerr)/100,
                  compiler = stringr::str_remove(compiler, "^build-") |>
                    stringr::str_remove("/$")
    )
}

#' Return the quadrature fractional error of a sum or difference
#'
#' @param a, b the values being summed or subtracted
#' @param da, db the error estimates for a and b
#'
#' @return (x/dx) = sqrt((da/a)**2 + (db/b)**2)
#' @export
#'
quadrature_error <- function(a, da, b, db)
{
  sqrt((da/a)**2 + (db/b)**2)
}

make_means <- function(tbl)
{
  tbl |>
    dplyr::group_by(compiler, func) |>
    dplyr::summarize(t = mean(time),
                     dt = sd(time),
                     .groups = "drop") |>
    tidyr::pivot_wider(id_cols = compiler,
                       names_from = func,
                       values_from = c(t, dt)) |>
    dplyr::mutate(template = t_template - t_constructor,
                  handopt = t_handopt - t_constructor,
                  dtemplate = template * quadrature_error(t_template, dt_template, t_constructor, dt_constructor),
                  dhandopt = handopt * quadrature_error(t_handopt, dt_handopt, t_constructor, dt_constructor))
}

make_for_scatterplot <- function(meanstbl)
{
  meanstbl |>
    dplyr::mutate(x=template, xmin=template-dtemplate, xmax=template+dtemplate,
                  y=handopt, ymin=handopt-dhandopt, ymax=handopt+dhandopt)
}
