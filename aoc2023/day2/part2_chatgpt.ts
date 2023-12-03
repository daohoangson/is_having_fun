import * as fs from "fs";

type CubeCounts = { red: number; green: number; blue: number };

function findMinimumSet(subsets: CubeCounts[]): CubeCounts {
  const minCounts = { red: 0, green: 0, blue: 0 };

  subsets.forEach((subset) => {
    minCounts.red = Math.max(minCounts.red, subset.red);
    minCounts.green = Math.max(minCounts.green, subset.green);
    minCounts.blue = Math.max(minCounts.blue, subset.blue);
  });

  return minCounts;
}

function parseGameSubset(subset: string): CubeCounts {
  const colors = { red: 0, green: 0, blue: 0 };
  const regex = /(\d+) (red|green|blue)/g;
  let match;

  while ((match = regex.exec(subset)) !== null) {
    colors[match[2] as keyof CubeCounts] += parseInt(match[1], 10);
  }

  return colors;
}

function sumOfPowers(input: string): number {
  const games = input.split("\n");
  let sum = 0;

  games.forEach((game) => {
    const [, subsetsPart] = game.split(":").map((p) => p.trim());
    const subsets = subsetsPart.split(";").map((p) => p.trim());
    const cubeCounts = subsets.map(parseGameSubset);
    const minSet = findMinimumSet(cubeCounts);
    const power = minSet.red * minSet.green * minSet.blue;
    sum += power;
  });

  return sum;
}

(async function () {
  const input = fs.readFileSync("day2/input.txt", "utf8");
  console.log(sumOfPowers(input));
})();
