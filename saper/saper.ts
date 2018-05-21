/// <reference path="jquery.d.ts"/>

enum Flag {
    Hidden, Visible, Flagged
}

abstract class Board {
    private static readonly LEFT_MOUSE: number = 1;
    private static readonly MIDDLE_MOUSE: number = 2;
    protected static readonly DISTANCE_EMPTY: number = 0;
    protected static readonly DISTANCE_BOMB: number = -1;
    protected static readonly BOMBS_COUNT: number = 40;
    protected static readonly SIZE: number = 16;
    protected readonly background_colour: string;
    protected readonly face_image: string;
    protected distances: Array<number>;
    protected flags: Array<Flag>;
    protected flagsLeft: number;
    protected clicks: number;

    constructor(background_colour: string, face_image: string) {
        this.background_colour = background_colour;
        this.face_image = face_image;
        this.beginNewGame();
    }

    protected restart() {
        this.distances = [];
        this.flags = [];
        this.flagsLeft = Board.BOMBS_COUNT;
        this.clicks = 0;

        for (let i = 0; i < Board.SIZE * Board.SIZE; ++i) {
            this.distances.push(Board.DISTANCE_EMPTY);
            this.flags.push(Flag.Hidden);
        }
    }

    protected leftClick(element: Element): void {
        ++this.clicks;
        $("div#clicks").html(String(this.clicks));
    }

    protected middleClick(element: Element): void {
        let pos = parseInt(element.id, 10);

        this.changeFlag(pos);
        $("div#flags").html(String(this.flagsLeft));
    }

    protected endGame(isWinning: boolean): void {
        $("div.field").off("mousedown");
        $("div.field").on("mousedown", this.clickNothing);

        if (isWinning)
            $("div.face").css({ "background-image": "url(\"images/winface.jpg\")" });
        else {
            this.showBombs();
            $("div.face").css({ "background-image": "url(\"images/sadface.jpg\")" });
        }
    }

    protected abstract getFieldsWithBombs(): JQuery<HTMLElement>;

    protected randBombs(count: number, posClicked: number, isOnClicked: boolean): Array<number> {
        let pos: number = 0;
        let bombs: Array<number> = isOnClicked ? [posClicked] : [];
        let factor = Board.SIZE * Board.SIZE - 1;

        for (let i = 0; i < count; ++i) {
            do
                pos = Math.floor(Math.random() * factor);
            while (bombs.indexOf(pos) >= 0 || this.isNeighbour(posClicked, pos));

            bombs.push(pos);
        }

        return bombs;
    }

    protected abstract increaseShots(pos: number): void;

    protected abstract decreaseShots(pos: number): void;

    private beginNewGame(): void {
        $("div.field").off("mousedown");
        this.restart();

        $("div.field")
            .on("mousedown", this.mouseClicked.bind(this))
            .css({
                "background-color": this.background_colour,
                "background-image": "none",
                "border-style": "outset",
                "border-color": "black"
            })
            .html("");
        $("div.face").css({ "background-image": this.face_image }).on("click", startNormalGame);
        $("div#clicks").html(String(this.clicks));
        $("div#flags").html(String(this.flagsLeft));
        $("div.counter").on("click", startTrollGame);
    }

    private mouseClicked(event: JQuery.Event<Element>): void {
        if (event.which == Board.LEFT_MOUSE)
            this.leftClick(event.target);
        else if (event.which == Board.MIDDLE_MOUSE)
            this.middleClick(event.target);
    }

    private showBombs(): void {
        this.getFieldsWithBombs()
            .css({
                "background-image": "url(\"images/bomba.jpg\")",
                "background-size": "100% 100%",
                "border-style": "solid"
            });
    }

    private changeFlag(pos: number): void {
        if (this.flags[pos] == Flag.Hidden) {
            this.flags[pos] = Flag.Flagged;
            --this.flagsLeft;
            $("div#" + pos).css({ "background-color": "green" });
            this.increaseShots(pos);
        }
        else if (this.flags[pos] == Flag.Flagged) {
            this.flags[pos] = Flag.Hidden;
            ++this.flagsLeft;
            $("div#" + pos).css({ "background-color": this.background_colour });
            this.decreaseShots(pos);
        }
    }

    private isNeighbour(pos1: number, pos2: number): boolean {
        let row: number = Math.floor(pos1 / NormalBoard.SIZE);
        let column: number = pos1 % NormalBoard.SIZE;

        if (pos2 == pos1)
            return true;

        if (row > 0 && column > 0 && pos2 == pos1 - NormalBoard.SIZE - 1)
            return true;

        if (row > 0 && pos2 == pos1 - NormalBoard.SIZE)
            return true;

        if (row > 0 && column < NormalBoard.SIZE - 1 && pos2 == pos1 - NormalBoard.SIZE + 1)
            return true;

        if (column > 0 && pos2 == pos1 - 1)
            return true;

        if (column < NormalBoard.SIZE - 1 && pos2 == pos1 + 1)
            return true;

        if (row < NormalBoard.SIZE - 1 && column > 0 && pos2 == pos1 + NormalBoard.SIZE - 1)
            return true;

        if (row < NormalBoard.SIZE - 1 && pos2 == pos1 + NormalBoard.SIZE)
            return true;

        if (row < NormalBoard.SIZE - 1 && column < NormalBoard.SIZE - 1
            && pos2 == pos1 + NormalBoard.SIZE + 1)
            return true;

        return false;
    }

    private clickNothing(event: JQuery.Event<Element>): void {
    }
}

class NormalBoard extends Board {
    private correctShots: number;
    private isGenerated: boolean;

    constructor() {
        super("#BBBBBB", "url(\"images/epicface.jpg\")");
    }

    protected restart(): void {
        super.restart();
        this.correctShots = 0;
        this.isGenerated = false;
    }

    protected getFieldsWithBombs(): JQuery<HTMLElement> {
        return $("div.field")
            .filter((index: number, elem: Element) =>
                this.isBomb(parseInt(elem.id, 10))
            );
    }

    protected leftClick(element: Element): void {
        super.leftClick(element);

        let pos: number = parseInt(element.id, 10);

        if (this.flags[pos] == Flag.Hidden) {
            if (!this.isGenerated)
                this.generate(pos);

            if (this.isBomb(pos)) {
                this.endGame(false);
            }
            else if (this.isEmpty(pos))
                this.bfs(pos);
            else
                this.setVisible(pos);
        }
    }

    protected middleClick(element: Element): void {
        super.middleClick(element);

        if (this.correctShots == NormalBoard.BOMBS_COUNT)
            this.endGame(true);
    }

    protected increaseShots(pos: number): void {
        if (this.isBomb(pos))
            ++this.correctShots;
    }

    protected decreaseShots(pos: number): void {
        if (this.isBomb(pos))
            --this.correctShots;
    }

    private generate(startingPos: number): void {
        let bombs = this.randBombs(NormalBoard.BOMBS_COUNT, startingPos, false);
        this.isGenerated = true;

        for (let i = 0; i < bombs.length; ++i) {
            let row: number = Math.floor(bombs[i] / NormalBoard.SIZE);
            let column: number = bombs[i] % NormalBoard.SIZE;

            this.distances[bombs[i]] = NormalBoard.DISTANCE_BOMB;

            if (row > 0 && column > 0
                && !this.isBomb(bombs[i] - NormalBoard.SIZE - 1))
                ++this.distances[bombs[i] - NormalBoard.SIZE - 1];

            if (row > 0 && !this.isBomb(bombs[i] - NormalBoard.SIZE))
                ++this.distances[bombs[i] - NormalBoard.SIZE];

            if (row > 0 && column < NormalBoard.SIZE - 1
                && !this.isBomb(bombs[i] - NormalBoard.SIZE + 1))
                ++this.distances[bombs[i] - NormalBoard.SIZE + 1];

            if (column > 0 && !this.isBomb(bombs[i] - 1))
                ++this.distances[bombs[i] - 1];

            if (column < NormalBoard.SIZE - 1 && !this.isBomb(bombs[i] + 1))
                ++this.distances[bombs[i] + 1];

            if (row < NormalBoard.SIZE - 1 && column > 0
                && !this.isBomb(bombs[i] + NormalBoard.SIZE - 1))
                ++this.distances[bombs[i] + NormalBoard.SIZE - 1];

            if (row < NormalBoard.SIZE - 1
                && !this.isBomb(bombs[i] + NormalBoard.SIZE))
                ++this.distances[bombs[i] + NormalBoard.SIZE];

            if (row < NormalBoard.SIZE - 1 && column < NormalBoard.SIZE - 1
                && !this.isBomb(bombs[i] + NormalBoard.SIZE + 1))
                ++this.distances[bombs[i] + NormalBoard.SIZE + 1];
        }
    }

    private bfs(posBeg: number) {
        let queue: Array<number> = [posBeg];

        this.setVisible(posBeg);

        while (queue.length > 0) {
            let pos: number = queue.shift();
            let row: number = Math.floor(pos / NormalBoard.SIZE);
            let column: number = pos % NormalBoard.SIZE;

            if (this.isEmpty(pos)) {
                if (row > 0 && column > 0
                    && this.flags[pos - NormalBoard.SIZE - 1] == Flag.Hidden) {
                    this.setVisible(pos - NormalBoard.SIZE - 1);

                    if (!this.isBomb(pos - NormalBoard.SIZE - 1))
                        queue.push(pos - NormalBoard.SIZE - 1);
                }

                if (row > 0 && this.flags[pos - NormalBoard.SIZE] == Flag.Hidden) {
                    this.setVisible(pos - NormalBoard.SIZE);

                    if (!this.isBomb(pos - NormalBoard.SIZE))
                        queue.push(pos - NormalBoard.SIZE);
                }

                if (row > 0 && column < NormalBoard.SIZE - 1
                    && this.flags[pos - NormalBoard.SIZE + 1] == Flag.Hidden) {
                    this.setVisible(pos - NormalBoard.SIZE + 1);

                    if (!this.isBomb(pos - NormalBoard.SIZE + 1))
                        queue.push(pos - NormalBoard.SIZE + 1);
                }

                if (column > 0 && this.flags[pos - 1] == Flag.Hidden) {
                    this.setVisible(pos - 1);

                    if (!this.isBomb(pos - 1))
                        queue.push(pos - 1);
                }

                if (column < NormalBoard.SIZE - 1 && this.flags[pos + 1] == Flag.Hidden) {
                    this.setVisible(pos + 1);

                    if (!this.isBomb(pos + 1))
                        queue.push(pos + 1);
                }

                if (row < NormalBoard.SIZE - 1 && column > 0
                    && this.flags[pos + NormalBoard.SIZE - 1] == Flag.Hidden) {
                    this.setVisible(pos + NormalBoard.SIZE - 1);

                    if (!this.isBomb(pos + NormalBoard.SIZE - 1))
                        queue.push(pos + NormalBoard.SIZE - 1);
                }

                if (row < NormalBoard.SIZE - 1
                    && this.flags[pos + NormalBoard.SIZE] == Flag.Hidden) {
                    this.setVisible(pos + NormalBoard.SIZE);

                    if (!this.isBomb(pos + NormalBoard.SIZE))
                        queue.push(pos + NormalBoard.SIZE);
                }

                if (row < NormalBoard.SIZE - 1 && column < NormalBoard.SIZE - 1
                    && this.flags[pos + NormalBoard.SIZE + 1] == Flag.Hidden) {
                    this.setVisible(pos + NormalBoard.SIZE + 1);

                    if (!this.isBomb(pos + NormalBoard.SIZE + 1))
                        queue.push(pos + NormalBoard.SIZE + 1);
                }
            }
        }
    }

    private setVisible(pos: number) {
        this.flags[pos] = Flag.Visible;
        $("div#" + pos).css({ "border-style": "solid", "border-color": "#E6E6E6" });

        if (this.distances[pos] > 0)
            $("div#" + pos).html(String(this.distances[pos]));
    }

    private isBomb(pos: number): boolean {
        return this.distances[pos] == Board.DISTANCE_BOMB;
    }

    private isEmpty(pos: number): boolean {
        return this.distances[pos] == Board.DISTANCE_EMPTY;
    }
}

class TrollBoard extends Board {
    private lastClickPos: number;

    constructor() {
        super("#DDDDDD", "url(\"images/trollface.jpg\")");
    }

    protected restart(): void {
        super.restart();
    }

    protected getFieldsWithBombs(): JQuery<HTMLElement> {
        let bombs: Array<number> =
            this.randBombs(NormalBoard.BOMBS_COUNT - 1, this.lastClickPos, true);

        return $("div.field")
            .filter((index: number, elem: Element) =>
                bombs.indexOf(parseInt(elem.id, 10)) >= 0
            );
    }

    protected leftClick(element: Element): void {
        super.leftClick(element);

        let pos = parseInt(element.id, 10);

        this.lastClickPos = pos;

        if (this.flags[pos] == Flag.Hidden) {
            this.endGame(false);
        }
    }

    protected middleClick(element: Element): void {
        super.middleClick(element);
    }

    protected increaseShots(pos: number): void {
    }

    protected decreaseShots(pos: number): void {
    }
}

let board: Board = null;

function startNormalGame(): void {
    board = new NormalBoard();
}

function startTrollGame(): void {
    board = new TrollBoard();
}

$(document).ready(startNormalGame);
