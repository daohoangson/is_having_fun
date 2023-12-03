// https://chat.openai.com/share/62390354-f1c8-4561-9db3-a6df12b8a7c0
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

  return colors;
}

function sumOfPossibleGames(input: string): number {
  const games = input.split("\n");
  const limits = { red: 12, green: 13, blue: 14 };
  let sum = 0;

  games.forEach((game) => {
    const [idPart, ...subsets] = game.split(": ")[1].split("; ");
    const gameId = parseInt(idPart, 10);
    const cubeCounts = subsets.map(parseGameSubset);

    if (isGamePossible(cubeCounts, limits)) {
      sum += gameId;
    }
  });

  return sum;
}

// Example usage
const input = `Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\nGame 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\nGame 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\nGame 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\nGame 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green`;
console.log(sumOfPossibleGames(input));
