import * as fs from "fs";

type CubeCounts = { red: number; green: number; blue: number };

function isGamePossible(subsets: CubeCounts[], limits: CubeCounts): boolean {
  const maxCounts = { red: 0, green: 0, blue: 0 };

  subsets.forEach((subset) => {
    maxCounts.red = Math.max(maxCounts.red, subset.red);
    maxCounts.green = Math.max(maxCounts.green, subset.green);
    maxCounts.blue = Math.max(maxCounts.blue, subset.blue);
  });

  return (
    maxCounts.red <= limits.red &&
    maxCounts.green <= limits.green &&
    maxCounts.blue <= limits.blue
  );
}

function parseGameSubset(subset: string): CubeCounts {
  const colors = { red: 0, green: 0, blue: 0 };
  const regex = /(\d+) (red|green|blue)/g;
  let match;

  while ((match = regex.exec(subset)) !== null) {
    colors[match[2] as keyof CubeCounts] += parseInt(match[1], 10);
  }

  console.log({ colors });

  return colors;
}

function sumOfPossibleGames(input: string): number {
  const games = input.split("\n");
  const limits: CubeCounts = { red: 12, green: 13, blue: 14 };
  let sum = 0;

  games.forEach((game) => {
    const [idPart, subsetsPart] = game.split(":").map((p) => p.trim());
    const subsets = subsetsPart.split(";").map((p) => p.trim());
    console.log({ idPart, subsets });
    const gameId = parseInt(idPart.match(/^Game (\d+)$/)![1], 10);
    const cubeCounts = subsets.map(parseGameSubset);
    console.log({ gameId, cubeCounts });

    if (isGamePossible(cubeCounts, limits)) {
      sum += gameId;
    }
  });

  return sum;
}

(async function () {
  const input = fs.readFileSync("day2/input.txt", "utf8");
  console.log(sumOfPossibleGames(input));
})();
