import { argv } from 'process';
import { readFileSync } from 'fs';

function verify(line, exclude_idx) {
    let nums = line.trim()
        .split(' ')
        .map((x) => parseInt(x));

    if (exclude_idx !== -1) {
        nums.splice(exclude_idx, 1);
    }

    let is_safe = true;
    let increasing = nums[1] - nums[0] > 0;
    for (let i = 1; i < nums.length; i++) {
        let safe;
        if (increasing) {
            safe = 1 <= nums[i] - nums[i - 1] && nums[i] - nums[i - 1] <= 3;
        } else {
            safe = 1 <= nums[i - 1] - nums[i] && nums[i - 1] - nums[i] <= 3;
        }
        is_safe &&= safe;
    }

    if (exclude_idx === -1 && !is_safe) {
        for (let i = 0; i < nums.length; i++) {
            is_safe ||= verify(line, i);
        }
    }

    return is_safe;
}

let reports = readFileSync(argv[2], {encoding: 'utf-8'});

let safe_count = reports.trim()
    .split('\n')
    .map((x) => verify(x, -1))
    .reduce((acc, x) => acc + x, 0);
console.log(safe_count);
