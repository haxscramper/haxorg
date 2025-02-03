import { Block, InlineContent, BlockNoteSchema, defaultBlockSchema, defaultBlockSpecs, defaultInlineContentSpecs, defaultStyleSpecs } from "@blocknote/core";
import { useCreateBlockNote } from "@blocknote/react";

enum OrgSemKind {
  Word,
  Space,
  Subtree,
  Paragrah,
}

class Org {
  getKind(): OrgSemKind { throw "base class does not implement get kind"; }
  public subnodes: Org[] = Array();
}

class Paragrah extends Org {
  getKind(): OrgSemKind { return OrgSemKind.Paragrah; }
}

class Subtree extends Org {
  getKind(): OrgSemKind {
    return OrgSemKind.Subtree;
  }
  public level: number = 0;
  public title: Paragrah;
}

const schema = BlockNoteSchema.create({
  blockSpecs: {
    // enable the default blocks if desired
    ...defaultBlockSpecs,

    // Add your own custom blocks:
    // customBlock: CustomBlock,
  },
  inlineContentSpecs: {
    // enable the default inline content if desired
    ...defaultInlineContentSpecs,

    // Add your own custom inline content:
    // customInlineContent: CustomInlineContent,
  },
  styleSpecs: {
    // enable the default styles if desired
    ...defaultStyleSpecs,

    // Add your own custom styles:
    // customStyle: CustomStyle
  },
});

type OrgBlock = Block<typeof schema.blockSchema, typeof schema.inlineContentSchema, typeof schema.styleSchema>;
type OrgInlineContent = InlineContent<typeof schema.inlineContentSchema, typeof schema.styleSchema>;

function orgAstToBlockNote(orgNode: Org): OrgBlock[] {
  const blocks: OrgBlock[] = [];
  return blocks;
}

function blockNoteToOrgAst(blocks: Block[]): Org {
  const root = new Org();
  return root;
}


export class OrgEditor {
  private editor: import("@blocknote/core").BlockNoteEditor | null = null;
  private currentPath: string | null = null;
  private currentContent: Org | null = null;
  private saveTimeout: number | null = null;

  async initializeEditor(container: HTMLElement) {
    const { BlockNoteEditor } = await import("@blocknote/core");

    if (this.currentPath) {
      this.editor = useCreateBlockNote({
        initialContent: [
          {
            type: "paragraph",
            content: "Welcome to this demo!",
          },
          {
            type: "heading",
            content: "This is a heading block",
          },
          {
            type: "paragraph",
            content: "This is a paragraph block",
          },
          {
            type: "paragraph",
          },
        ],
      });
    }
  }

}

