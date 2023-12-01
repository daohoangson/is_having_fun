import { readFileSync } from "fs";

function firstOf(line: string): string {
  for (let i = 0; i < line.length; i++) {
    const c = line[i];
    if (c >= "0" && c <= "9") {
      return c;
    }
  }

  throw new Error(`There is no digit in ${line}`);
}

function lastOf(line: string): string {
  for (let i = line.length; i > -1; i--) {
    const c = line[i];
    if (c >= "0" && c <= "9") {
      return c;
    }
  }

  throw new Error(`There is no digit in ${line}`);
}

(async function main() {
  const input: string = readFileSync("day1/input.txt", "utf8");
  const lines = input.split("\n").filter((line) => line.length > 0);
  let sum = 0;
  for (const line of lines) {
    sum += parseInt(firstOf(line) + lastOf(line), 10);
  }
  console.log({ sum });
})();
