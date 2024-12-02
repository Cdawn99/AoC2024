import { argv } from 'process';
import { readFileSync } from 'fs';

function verify(line) {
    let nums = line.trim()
        .split(' ')
        .map((x) => parseInt(x));

    let is_safe = true;
    let increasing = nums[1] - nums[0] > 0;
    for (let i = 1; i < nums.length; i++) {
        if (increasing) {
            is_safe &&= 1 <= nums[i] - nums[i - 1] && nums[i] - nums[i - 1] <= 3;
        } else {
            is_safe &&= 1 <= nums[i - 1] - nums[i] && nums[i - 1] - nums[i] <= 3;
        }
    }
    return is_safe;
}

let reports = readFileSync(argv[2], {encoding: 'utf-8'});

let safe_count = reports.trim()
                        .split('\n')
                        .map((x) => verify(x))
                        .reduce((acc, x) => acc + x, 0);
console.log(safe_count);
