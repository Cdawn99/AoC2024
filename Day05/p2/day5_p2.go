package main

import (
    "fmt"
    "log"
    "os"
    "slices"
    "strconv"
    "strings"
)

func main() {
    program := os.Args[0]
    fp := os.Args[1:]

    if (len(fp) != 1) {
        fmt.Printf("Usage: %v <page_info.txt>\n", program)
        os.Exit(1)
    }

    page_info_bytes, err := os.ReadFile(fp[0])
    if err != nil {
        log.Fatalf("Failed to open file %v\n", fp[0])
    }
    page_info_str := string(page_info_bytes)
    page_info_slice := strings.Split(strings.TrimSpace(page_info_str), "\n\n")

    rules := strings.Split(strings.TrimSpace(page_info_slice[0]), "\n")

    rev_adj_map := make(map[string][]string)
    for _, v := range rules {
        vs := strings.Split(v, "|")
        pre := vs[0]
        post := vs[1]
        rev_adj_map[post] = append(rev_adj_map[post], pre)
    }

    updates := strings.Split(strings.TrimSpace(page_info_slice[1]), "\n")
    middle_sum := 0
    for _, update := range updates {
        pages := strings.Split(update, ",")
        pages_count := len(pages)

        is_correct_order := true
        for i := 0; i < pages_count; i++ {
            prev_pages := rev_adj_map[pages[i]]
            for j := i + 1; j < pages_count; j++ {
                if slices.Contains(prev_pages, pages[j]) {
                    is_correct_order = false
                    break
                }
            }
            if !is_correct_order {
                break
            }
        }
        if is_correct_order {
            continue
        }

        for i := 0; i < pages_count - 1; i++ {
            swapped := true
            for swapped {
                prev_pages := rev_adj_map[pages[i]]
                for j := i + 1; j < pages_count; j++ {
                    if slices.Contains(prev_pages, pages[j]) {
                        pages[i], pages[j] = pages[j], pages[i]
                        swapped = true
                        break
                    }
                    swapped = false
                }
            }
        }

        mid_idx := pages_count / 2
        mid_val, err := strconv.Atoi(pages[mid_idx])
        if err != nil {
            log.Fatalf("Filed to convert %v to int\n", pages[mid_idx])
        }
        middle_sum += mid_val
    }

    fmt.Printf("Sum of middle pages: %v\n", middle_sum)
}
